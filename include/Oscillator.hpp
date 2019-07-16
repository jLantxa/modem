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

class Oscillator {
public:
    Oscillator(unsigned int freq, unsigned int sampleRate);
    ~Oscillator();

    float operator[](unsigned int n);
    float atPhase(float phy);

    unsigned int length();

private:
    unsigned int mFreq;
    unsigned int mSampleRate;
    unsigned int mLength;

    float* mSamples;
};

#endif // _MODEM_INCLUDE_OSCILLATOR_HPP_
