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

#include <iostream>

#include "fourier.hpp"

const static char* LOG_TAG = "FFT_Test";

void printComplexArray(const char* name, ComplexSymbol* arr, unsigned int size) {
    std::cout << name << " =" << std::endl;
    for (unsigned int i = 0; i < size; i++) {
        std::cout << "\t(" << arr[i].real() << ", " << arr[i].imag() << ")" << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    ComplexSymbol x[] = {
        ComplexSymbol(1),
        ComplexSymbol(0),
        ComplexSymbol(1),
        ComplexSymbol(0)
    };

    ComplexSymbol y[4];
    ComplexSymbol z[4];

    dct(4, x, y);
    idct(4, y, z);

    printComplexArray("x", x, 4);
    printComplexArray("y = dct(x)", y, 4);
    printComplexArray("z = idct(y)", z, 4);

    return 0;
}
