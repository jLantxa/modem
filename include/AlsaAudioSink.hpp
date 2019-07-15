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

    virtual void send(AudioRingBuffer& buffer);

private:
    snd_pcm_t *mPCMHandle;
    snd_pcm_hw_params_t *mHWParams;

    unsigned int mSampleRate;
};

#endif // _MODEM_INCLUDE_ALSA_AUDIO_SINK_HPP_
