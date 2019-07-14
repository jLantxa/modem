/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#include "AudioInterface.hpp"

class AlsaAudioSink : public IAudioSink {
public:
    AlsaAudioSink();
    virtual ~AlsaAudioSink();

    virtual void send(AudioRingBuffer& buffer);

private:
    snd_pcm_t *mPCMHandle;
    snd_pcm_hw_params_t *mHWParams;

    void config();
};
