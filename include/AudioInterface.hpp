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

#ifndef _MODEM_INCLUDE_AUDIO_INTERFACE_HPP_
#define _MODEM_INCLUDE_AUDIO_INTERFACE_HPP_

namespace modem {

class IAudioSink {
public:
    virtual ~IAudioSink() = default;
    virtual unsigned int send(float* buffer, unsigned int size) = 0;
};

}  // namespace modem

#endif  // _MODEM_INCLUDE_AUDIO_INTERFACE_HPP_
