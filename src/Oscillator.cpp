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
