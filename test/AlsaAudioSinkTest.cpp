/*
 * This source file is part of Modem
 * Copyright (C) 2019  Javier Lancha Vázquez
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

#include "debug.hpp"

#include "AlsaAudioSink.hpp"
#include "NCO.hpp"

const static char* LOG_TAG = "AlsaAudioSinkTest";

#define PULSE_TIME_SECONDS 3
#define FRAME_SIZE 1024

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        Debug::Log::e(LOG_TAG, "./AlsaAudioSinkTest <freq> <sample_rate>");
        return -1;
    }

    const unsigned int freq = atoi(argv[1]);
    const unsigned int sample_rate = atoi(argv[2]);

    IAudioSink* audioSink = new AlsaAudioSink(sample_rate);

    NCO oscillator(freq, sample_rate, 12 /* Table index bits */);

    const unsigned int max_sample = sample_rate * PULSE_TIME_SECONDS;
    unsigned int n = 0;
    float buffer[FRAME_SIZE];
    while (n < max_sample) {
        for (unsigned int i = 0; i < FRAME_SIZE; i++) {
            buffer[i] = oscillator();
        }
        audioSink->send(buffer, FRAME_SIZE);
        n += FRAME_SIZE;
    }

    Debug::Log::i(LOG_TAG, "TEST END");
    delete audioSink;
    return 0;
}
