/*
 * This source file is part of Modem
 * Copyright (C) 2021  Javier Lancha Vázquez
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

#ifndef _MODEM_INCLUDE_FSK_HPP_
#define _MODEM_INCLUDE_FSK_HPP_

#include <cstdint>

#include "oscillator.hpp"

namespace modem {

struct FSKConfig {
    uint32_t sample_rate;
    uint16_t baud_rate;
    uint16_t f0;
    uint16_t f1;
};

class FSKMod {
public:
    FSKMod(FSKConfig config);

    uint16_t GetSymbolLength() const;
    const FSKConfig& GetConfig() const;

    void EncodeSymbol(uint8_t symbol, float* buffer);

private:
    const FSKConfig m_config;
    modem::TrigonometryLUT m_trig_table;
    modem::SineOscillator m_oscillator;

    unsigned int m_symbol_length;
};

}  // namespace modem

#endif  // _MODEM_INCLUDE_FSK_HPP_