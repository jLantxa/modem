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

#include "oscillator.hpp"

#include <algorithm>
#include <cmath>

SineLUT::SineLUT(unsigned int bits) {
    bit_depth = std::min<unsigned int>(MAX_TABLE_BITS, bit_depth);
    length = 1 << bit_depth;
    mask = length - 1;

    table = new float[length];
    for (unsigned int k = 0; k < length; k++) {
        table[k] = sin(2*M_PI * k/(double)length);
    }
}

SineLUT::~SineLUT() {
    delete[] table;
}

float SineLUT::operator[](unsigned int i) {
    return table[i & mask];
}


NCO::NCO(const float freq, const float sampleRate, struct SineLUT* table)
:   mTable(table),
    mFrequency(freq),
    mSampleRate(sampleRate),
    mPhase(0),
    mDeltaPhase(0)
{
    updatePhaseDelta();
}

NCO::~NCO() {

}

void NCO::updatePhaseDelta() {
    mDeltaPhase = (unsigned int)(mFrequency * SineLUT::ROTATION / mSampleRate);
}

float NCO::operator()(void) {
    mPhase += mDeltaPhase;
    const unsigned int index = mPhase >> (sizeof(unsigned)*8 - mTable->bit_depth);
    return (*mTable)[index];
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
