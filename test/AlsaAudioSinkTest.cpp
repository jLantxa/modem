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

#include <algorithm>

const static char* LOG_TAG = "AlsaAudioSinkTest";

int main(int argc, char const *argv[])
{
    if (argc != 5) {
        Debug::Log::e(LOG_TAG, "./AlsaAudioSinkTest <freq0> sample_rate> <time> <notes>");
        return -1;
    }

    unsigned int freq = atoi(argv[1]);
    const unsigned int sample_rate = atoi(argv[2]);
    const float time = atof(argv[3]);
    const unsigned int notes = std::max(1, atoi(argv[4]));

    IAudioSink* audioSink = new AlsaAudioSink(sample_rate);

    NCO oscillator(freq, sample_rate, 16/*bits for table index*/);

    const unsigned int total_samples = static_cast<unsigned int>(sample_rate * time);
    const unsigned int frame_size = static_cast<unsigned int>(total_samples/(float)notes);
    unsigned int n = 0;
    float buffer[frame_size];
    while (n < total_samples) {
        for (unsigned int i = 0; i < frame_size; i++) {
            buffer[i] = oscillator();
        }
        audioSink->send(buffer, frame_size);
        freq = std::min<float>(freq*pow(2, 1/12.0f), sample_rate/2.0f);
        oscillator.setFrequency(freq);
        n += frame_size;
    }

    Debug::Log::i(LOG_TAG, "TEST END");
    delete audioSink;
    return 0;
}
