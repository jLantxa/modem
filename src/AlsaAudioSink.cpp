/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#include "AudioInterface.hpp"

AlsaAudioSink::AlsaAudioSink() {
    config();
}

AlsaAudioSink::~AlsaAudioSink() {
    snd_pcm_drain(mPCMHandle);
	snd_pcm_close(mPCMHandle);
}

void AlsaAudioSink::config() {

}
