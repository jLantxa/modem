/*
 * This source file is part of Modem
 * Copyright (C) 2019, 2021  Javier Lancha Vázquez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
*/

#define NDEBUG 0

#include <algorithm>

#include "debug.hpp"

#include "AlsaAudioSink.hpp"
#include "fsk.hpp"

const static char* LOG_TAG = "modem";

int main(int argc, char const *argv[])
{
    if (argc != 6) {
        jltx::debug::Log.e(LOG_TAG, "%s <sample_rate> <baud_rate> <f0> <f1> <text>", argv[0]);
        return -1;
    }

    const uint32_t sample_rate = atoi(argv[1]);
    const uint16_t baud_rate = atoi(argv[2]);
    const uint16_t f0 = atoi(argv[3]);
    const uint16_t f1 = atoi(argv[4]);
    const char* text = argv[5];

    modem::IAudioSink* audioSink = new modem::AlsaAudioSink(sample_rate);

    modem::FSKConfig fsk_config {
        .sample_rate = sample_rate,
        .baud_rate = baud_rate,
        .f0 = f0,
        .f1 = f1
    };

    modem::FSKMod fsk_mod(fsk_config);

    const unsigned int text_size = strlen(text);
    const uint16_t symbol_length = fsk_mod.GetSymbolLength();
    float buffer[symbol_length];

    for (unsigned int char_index = 0; char_index < text_size; char_index++) {
        fsk_mod.EncodeSymbol((uint8_t) text[char_index], buffer);
        audioSink->send(buffer, symbol_length);
    }

    delete audioSink;
    return 0;
}
