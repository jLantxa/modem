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
#include "oscillator.hpp"

const static char* LOG_TAG = "AlsaAudioSinkTest";

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        jltx::debug::Log.e(LOG_TAG, "%s <sample_rate> <freq> <time>", argv[0]);
        return -1;
    }

    const unsigned int sample_rate = atoi(argv[1]);
    const unsigned int freq = atoi(argv[2]);
    const float time = atof(argv[3]);

    modem::IAudioSink* audioSink = new modem::AlsaAudioSink(sample_rate);

    modem::TrigonometryLUT trigTable;
    modem::SineOscillator oscillator(freq, sample_rate, &trigTable);

    const unsigned int total_samples = static_cast<unsigned int>(sample_rate * time);
    float buffer[total_samples];

    for (unsigned int i = 0; i < total_samples; i++) {
        buffer[i] = oscillator();
    }

    audioSink->send(buffer, total_samples);

    delete audioSink;
    return 0;
}
