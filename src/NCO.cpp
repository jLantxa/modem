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

#include "NCO.hpp"

#include <algorithm>
#include <cmath>

NCO::NCO(const float freq, const float sampleRate, const unsigned int tableBits)
:   mFrequency(freq),
    mSampleRate(sampleRate),
    mPhase(0),
    mDeltaPhase(0)
{
    mTableBits = std::min<unsigned int>(MAX_TABLE_BITS, tableBits);
    mTableLength = 1 << mTableBits;
    mMask = mTableLength - 1;

    updatePhaseDelta();

    // Fill lookup table
    mTable = new float[mTableLength];
    for (unsigned int k = 0; k < mTableLength; k++) {
        mTable[k] =  sin(2 * M_PI * k / (double)mTableLength);
    }
}

NCO::~NCO() {
    delete[] mTable;
}

void NCO::updatePhaseDelta() {
    mDeltaPhase = (unsigned int)(mFrequency * ROTATION / mSampleRate);
}

float NCO::operator()(void) {
    mPhase += mDeltaPhase;
    const unsigned int index = mPhase >> (sizeof(unsigned)*8 - mTableBits);
	return mTable[index & mMask];
}

float NCO::frequency() const {
    return mFrequency;
}

void NCO::setFrequency(const float frequency) {
    mFrequency = frequency;
    updatePhaseDelta();
}

float NCO::sampleRate() const {
    return mSampleRate;
}

void NCO::setSampleRate(const float sampleRate) {
    mSampleRate = sampleRate;
    updatePhaseDelta();
}
