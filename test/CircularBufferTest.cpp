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

#define NDEBUG 0

#include <assert.h>
#include <iostream>

#include "CircularBuffer.hpp"

int main(int argc, char const *argv[])
{
    CircularBuffer<int> buf16(16);
    assert(buf12.length() == 16);

    CircularBuffer<int> buffer(64);
    assert(buffer.length() == 64);
    assert(buffer.size() == 0);

    const unsigned int push_length = 56;
    for (unsigned int i = 0; i < push_length; i++) {
        buffer.push(i);
    }
    assert(buffer.size() == push_length);
    std::cout <<
        "Pushed " << push_length << " items" << std::endl <<
        "Buffer size: " << buffer.size() << std::endl;

    const unsigned int pop_length = 48;
    for (unsigned int i = 0; i < pop_length; i++) {
        int item = buffer.consume();
        assert(item == i);
    }
    assert(buffer.size() == (push_length - pop_length));
    std::cout <<
        "Popped " << pop_length << " items" << std::endl <<
        "Buffer size: " << buffer.size() << std::endl;

    const unsigned int last_push_length = 32;
    for (unsigned int i = 0; i < last_push_length; i++) {
        buffer.push(i);
    }
    assert(buffer.size() == (push_length - pop_length + last_push_length));
    std::cout <<
        "Pushed " << last_push_length << " items" << std::endl <<
        "Buffer size: " << buffer.size() << std::endl;

    for (unsigned int i = 0; i < 128; i++) {
        buffer.push(i);
    }
    assert(buffer.size() == buffer.length());
    std::cout <<
        "Pushed 128 items, but buffer length is " << buffer.length() <<
        std::endl <<
        "Buffer size: " << buffer.size() << std::endl;

    std::cout << "ALL TESTS PASSED" << std::endl;
    return 0;
}
