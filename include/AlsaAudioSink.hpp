/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#ifndef _MODEM_INCLUDE_ALSA_AUDIO_SINK_HPP_
#define _MODEM_INCLUDE_ALSA_AUDIO_SINK_HPP_

#include <alsa/asoundlib.h>

#include "audio.hpp"
#include "AudioInterface.hpp"

class AlsaAudioSink : public IAudioSink {
public:
    AlsaAudioSink(unsigned int sampleRate);
    virtual ~AlsaAudioSink();

    virtual unsigned int send(float* buffer, unsigned int size);

    unsigned int sampleRate();

private:
    snd_pcm_t* mPCMHandle;

    unsigned int mSampleRate;
};

#endif // _MODEM_INCLUDE_ALSA_AUDIO_SINK_HPP_
