/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#define NDEBUG 0

#include <assert.h>
#include <iostream>

#include "AlsaAudioSink.hpp"

#include "CircularBuffer.hpp"

int main(int argc, char const *argv[])
{
    IAudioSink* audioSink = new AlsaAudioSink(44100);

    std::cout << "ALL TESTS PASSED" << std::endl;
    delete audioSink;
    return 0;
}
