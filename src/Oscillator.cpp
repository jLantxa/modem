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
        mSamples[n] = sin(n * (2*M_PI)*(mFreq/mSampleRate));
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
