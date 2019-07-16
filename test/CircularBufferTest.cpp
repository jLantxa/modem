/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
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
