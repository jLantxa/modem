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

#ifndef _MODEM_INCLUDE_OSCILLATOR_HPP_
#define _MODEM_INCLUDE_OSCILLATOR_HPP_

#include <cmath>

namespace modem {

struct TrigonometryLUT {
    unsigned int bit_depth;
    unsigned int length;
    unsigned int mask;
    float* table;

    static constexpr unsigned int DEFAULT_TABLE_BITS = 10;
    static constexpr unsigned int MAX_TABLE_BITS = 16;
    static constexpr float ROTATION = 2.0f * (1u << (8*sizeof(unsigned int) -1));

    TrigonometryLUT(unsigned int bits = DEFAULT_TABLE_BITS);
    ~TrigonometryLUT();

    float operator[](unsigned int i) const ;

    float sin(unsigned int i) const;
    float cos(unsigned int i) const;
    float tan(unsigned int i) const;
};

class NCO {
public:
    NCO(const float freq, const float sampleRate, const TrigonometryLUT& table);
    virtual ~NCO();

    float operator()();

    float frequency() const;
    void setFrequency(const float frequency);

    float sampleRate() const;
    void setSampleRate(const float sampleRate);

protected:
    const TrigonometryLUT& mTable;

    unsigned int mPhase;
    unsigned int mDeltaPhase;

    float mFrequency;
    float mSampleRate;

    virtual float lookUpTable(unsigned int index) const;

private:
    void resetPhaseDelta();
    unsigned int updatePhase() const;
};


class SineOscillator : public NCO {
public:
    SineOscillator(const float freq, const float sampleRate, const TrigonometryLUT& table);
    virtual ~SineOscillator() = default;

protected:
    float lookUpTable(unsigned int index) const override;
};


class CosineOscillator : public NCO {
public:
    CosineOscillator(const float freq, const float sampleRate, const TrigonometryLUT& table);
    virtual ~CosineOscillator() = default;

protected:
    float lookUpTable(unsigned int index) const override;
};

}  // namespace modem

#endif  // _MODEM_INCLUDE_OSCILLATOR_HPP_
