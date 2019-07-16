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

#include "debug.hpp"

#include "AlsaAudioSink.hpp"

#define PCM_DEVICE "default"
#define CHANNELS 1

const static char* LOG_TAG = "AlsaAudioSink";

AlsaAudioSink::AlsaAudioSink(unsigned int sampleRate)
{
	snd_pcm_hw_params_t* HWParams;

    unsigned int ret;
    if ((ret = snd_pcm_open(&mPCMHandle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		Debug::Log::e(LOG_TAG, "Cannot open \"%s\" PCM device. %s",
			PCM_DEVICE, snd_strerror(ret));
    }

	snd_pcm_hw_params_malloc(&HWParams);
	snd_pcm_hw_params_any(mPCMHandle, HWParams);

	if ((ret = snd_pcm_hw_params_set_access(mPCMHandle, HWParams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		Debug::Log::e(LOG_TAG, "Cannot set interleaved mode. %s", snd_strerror(ret));
    }

	if ((ret = snd_pcm_hw_params_set_format(mPCMHandle, HWParams, SND_PCM_FORMAT_FLOAT)) < 0) {
		Debug::Log::e(LOG_TAG, "Cannot set format. %s", snd_strerror(ret));
    }

	if ((ret = snd_pcm_hw_params_set_channels(mPCMHandle, HWParams, CHANNELS)) < 0) {
		Debug::Log::e(LOG_TAG, "Cannot set channels number. %s", snd_strerror(ret));
    }

	if ((ret = snd_pcm_hw_params_set_rate_near(mPCMHandle, HWParams, &sampleRate, 0)) < 0) {
		Debug::Log::e(LOG_TAG, "Cannot set rate. %s", snd_strerror(ret));
    }

	if ((ret = snd_pcm_hw_params(mPCMHandle, HWParams)) < 0) {
		Debug::Log::e(LOG_TAG, "Cannot set harware parameters. %s", snd_strerror(ret));
    }

	Debug::Log::i(LOG_TAG, "PCM name: '%s'", snd_pcm_name(mPCMHandle));
	Debug::Log::i(LOG_TAG, "PCM state: %s", snd_pcm_state_name(snd_pcm_state(mPCMHandle)));
    unsigned int reportedSampleRate;
	snd_pcm_hw_params_get_rate(HWParams, &reportedSampleRate, 0);
    mSampleRate = reportedSampleRate;
	Debug::Log::i(LOG_TAG, "rate: %d Hz", mSampleRate);

	snd_pcm_hw_params_free(HWParams);
	snd_pcm_prepare(mPCMHandle);
}

AlsaAudioSink::~AlsaAudioSink() {
    snd_pcm_drain(mPCMHandle);
	snd_pcm_close(mPCMHandle);
}

unsigned int AlsaAudioSink::send(float* buffer, unsigned int size) {
	if (size == 0) {	// Nothing to write
		return 0;
	}

	int ret = snd_pcm_writei(mPCMHandle, buffer, size);
	if (ret > 0) {
		return ret;
	} else {
		if (ret == -EPIPE) {
			snd_pcm_prepare(mPCMHandle);
		}
		return 0;
	}
}

unsigned int AlsaAudioSink::sampleRate() {
	return mSampleRate;
}
