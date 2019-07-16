/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#define NDEBUG 0

#include "debug.hpp"

#include "AlsaAudioSink.hpp"
#include "Oscillator.hpp"

#include "CircularBuffer.hpp"

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

    Oscillator osc(freq, sample_rate);

    const unsigned int max_sample = sample_rate * PULSE_TIME_SECONDS;
    unsigned int n = 0;
    float buffer[FRAME_SIZE];
    while (n < max_sample) {
        for (unsigned int i = 0; i < FRAME_SIZE; i++) {
            buffer[i] = osc[n+i];
        }
        audioSink->send(buffer, FRAME_SIZE);
        n += FRAME_SIZE;
    }

    Debug::Log::i(LOG_TAG, "TEST END");
    delete audioSink;
    return 0;
}
