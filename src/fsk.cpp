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

#include <cmath>

#include "debug.hpp"

#include "fsk.hpp"

const static char* LOG_TAG = "FSK";

namespace modem {

FSKMod::FSKMod(FSKConfig config)
:   m_config(config),
    m_trig_table(16),
    m_oscillator(m_config.f0, m_config.sample_rate, m_trig_table)
{
    const float samples_per_bit = static_cast<float>(m_config.sample_rate) / m_config.baud_rate;
    m_symbol_length = static_cast<unsigned int>(std::ceil(8 * samples_per_bit));
}

uint16_t FSKMod::GetSymbolLength() const {
    return m_symbol_length;
}

const FSKConfig& FSKMod::GetConfig() const {
    return m_config;
}

void FSKMod::EncodeSymbol(uint8_t symbol, float* buffer) {
    unsigned int sample = 0;
    for (unsigned int bit_num = 0; bit_num < 8; ++bit_num) {
        const uint8_t val = (symbol >> bit_num) & 0x01;
        const uint16_t freq = (val == 0)? m_config.f0 : m_config.f1;
        m_oscillator.setFrequency(freq);

        for (unsigned int i = 0; i < (m_symbol_length / 8); ++i) {
            buffer[sample++] = m_oscillator();
        }
    }
}

}  // namespace modem