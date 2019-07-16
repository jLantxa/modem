/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#include <cmath>

#include "Oscillator.hpp"

Oscillator::Oscillator(unsigned int freq, unsigned int sampleRate)
:   mFreq(freq), mSampleRate(sampleRate)
{
    // TODO: Last sample equals to the first sometimes?
    mLength = mSampleRate/mFreq;

    mSamples = new float[mLength];
    for (unsigned int n = 0; n < mLength; n++) {
        float t = 1.0f * n / mSampleRate;
        mSamples[n] = sin(2.0f * M_PI * freq * t);
    }
}

Oscillator::~Oscillator() {
    delete[] mSamples;
}

float Oscillator::operator[](unsigned int i) {
    return mSamples[i % mLength];
}

float Oscillator::atPhase(float phi) {
    unsigned int n = phi/(2*M_PI) * mLength;
    return  mSamples[n % mLength];
}

unsigned int Oscillator::length() {
    return mLength;
}
