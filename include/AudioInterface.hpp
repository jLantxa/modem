/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#ifndef _MODEM_INCLUDE_AUDIO_INTERFACE_HPP_
#define _MODEM_INCLUDE_AUDIO_INTERFACE_HPP_

#include "CircularBuffer.hpp"

class IAudioSink {
public:
    virtual ~IAudioSink() = default;
    virtual void send(AudioRingBuffer& buffer) = 0;
};

#endif // _MODEM_INCLUDE_AUDIO_INTERFACE_HPP_
