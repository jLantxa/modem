/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#include "CircularBuffer.hpp"

class IAudioSink {
public:
    virtual ~IAudioSink() = 0;

    virtual void send(AudioRingBuffer& buffer) = 0;
};
