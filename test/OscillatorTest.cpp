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
