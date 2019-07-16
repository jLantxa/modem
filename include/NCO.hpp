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

#ifndef _MODEM_INCLUDE_NCO_HPP_
#define _MODEM_INCLUDE_NCO_HPP_

#include <cmath>

class NCO final {
public:
    NCO(const float freq, const float sampleRate,
        const unsigned int tableBits = DEFAULT_TABLE_BITS);
    ~NCO();

    float operator()(void);

    float frequency() const;
    void setFrequency(const float frequency);

    float sampleRate() const;
    void setSampleRate(const float sampleRate);

    const static unsigned int DEFAULT_TABLE_BITS = 10;
    const static unsigned int MAX_TABLE_BITS = 16;

private:
    float* mTable;

    unsigned int mTableBits;
    unsigned int mTableLength;
    unsigned int mMask;
    unsigned int mPhase;
    unsigned int mDeltaPhase;

    float mFrequency;
    float mSampleRate;

    void updatePhaseDelta();

    const float ROTATION = pow(2, 8*sizeof(unsigned int));
};

#endif // _MODEM_INCLUDE_NCO_HPP_
