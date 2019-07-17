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

#ifndef _MODEM_INCLUDE_OSCILLATOR_HPP_
#define _MODEM_INCLUDE_OSCILLATOR_HPP_

#include <cmath>

struct SineLUT {
    unsigned int bit_depth;
    unsigned int length;
    unsigned int mask;
    float* table;

    const static unsigned int DEFAULT_TABLE_BITS = 10;
    const static unsigned int MAX_TABLE_BITS = 16;
    constexpr static float ROTATION = 2.0f * (1u << (8*sizeof(unsigned int) -1));

    SineLUT(unsigned int bits = DEFAULT_TABLE_BITS);
    ~SineLUT();

    float operator[](unsigned int i);
};

class NCO final {
public:
    NCO(const float freq, const float sampleRate, struct SineLUT* table);
    ~NCO();

    float operator()(void);

    float frequency() const;
    void setFrequency(const float frequency);

    float sampleRate() const;
    void setSampleRate(const float sampleRate);

private:
    struct SineLUT* mTable;

    unsigned int mPhase;
    unsigned int mDeltaPhase;

    float mFrequency;
    float mSampleRate;

    void updatePhaseDelta();
};

#endif // _MODEM_INCLUDE_OSCILLATOR_HPP_
