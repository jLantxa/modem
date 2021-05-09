/*
 * This source file is part of Modem
 * Copyright (C) 2019, 2021  Javier Lancha Vázquez
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
#include <cstdio>

#include <algorithm>

#include "oscillator.hpp"

namespace modem {

TrigonometryLUT::TrigonometryLUT(unsigned int bits) {
    bit_depth = std::min<unsigned int>(MAX_TABLE_BITS, bits);
    length = 1 << bit_depth;
    mask = length - 1;

    table = new float[length];
    for (unsigned int k = 0; k < length; k++) {
        table[k] = std::sin((2 * M_PI) * k / static_cast<float>(length+1));
    }
}

TrigonometryLUT::~TrigonometryLUT() {
    delete[] table;
}


float TrigonometryLUT::operator[](unsigned int i) const {
    return table[i & mask];
}

float TrigonometryLUT::sin(unsigned int i) const {
    return table[i & mask];
}

float TrigonometryLUT::cos(unsigned int i) const {
    return table[(i+(length>>2)) & mask];
}

float TrigonometryLUT::tan(unsigned int i) const{
    return table[i & mask] / table[(i+(length>>2)) & mask];
}

NCO::NCO(const float freq, const float sampleRate, const TrigonometryLUT& table)
:   mTable(table),
    mPhase(0),
    mDeltaPhase(0),
    mFrequency(freq),
    mSampleRate(sampleRate)

{
    resetPhaseDelta();
}

NCO::~NCO() {

}

void NCO::resetPhaseDelta() {
    mDeltaPhase = (unsigned int)(mFrequency * TrigonometryLUT::ROTATION / mSampleRate);
}

float NCO::operator()(void) {
    const unsigned int index = mPhase >> (sizeof(unsigned)*8 - mTable.bit_depth);
    float value = lookUpTable(index);
    mPhase += mDeltaPhase;
    return value;
}

float NCO::lookUpTable(unsigned int i) const {
    return mTable[i];
}

float NCO::frequency() const {
    return mFrequency;
}

void NCO::setFrequency(const float frequency) {
    mFrequency = frequency;
    resetPhaseDelta();
}

float NCO::sampleRate() const {
    return mSampleRate;
}

void NCO::setSampleRate(const float sampleRate) {
    mSampleRate = sampleRate;
    resetPhaseDelta();
}


SineOscillator::SineOscillator(const float freq, const float sampleRate, const TrigonometryLUT& table)
: NCO(freq, sampleRate, table) { }

float SineOscillator::lookUpTable(unsigned int i) const {
    return mTable.sin(i);
}

CosineOscillator::CosineOscillator(const float freq, const float sampleRate, const TrigonometryLUT& table)
: NCO(freq, sampleRate, table) { }

float CosineOscillator::lookUpTable(unsigned int i) const {
    return mTable.cos(i);
}

}  // namespace modem