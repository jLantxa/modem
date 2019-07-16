/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/
#include "debug.hpp"

#include "Oscillator.hpp"

const static char* LOG_TAG  = "OscillatorTest";

int main(int argc, char const *argv[])
{
    Oscillator osc(440, 8000);

    Debug::Log::i(LOG_TAG, "Oscillator length = %d", osc.length());

    for (unsigned int n = 0; n < osc.length(); n++) {
        Debug::Log::i(LOG_TAG, "x[%d] = %.5f", n, osc[n]);
    }

    return 0;
}
