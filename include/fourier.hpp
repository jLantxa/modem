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

#ifndef _MODEM_INCLUDE_FOURIER_HPP_
#define _MODEM_INCLUDE_FOURIER_HPP_

#include "signal.hpp"

void dct(unsigned int size, ComplexSymbol* src, ComplexSymbol* dst);
void idct(unsigned int size, ComplexSymbol* src, ComplexSymbol* dst);

#endif // _MODEM_INCLUDE_FOURIER_HPP_