/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
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
