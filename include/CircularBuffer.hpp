/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#ifndef _MODEM_INCLUDE_CIRCULAR_BUFFER_HPP_
#define _MODEM_INCLUDE_CIRCULAR_BUFFER_HPP_

#include <cmath>

template <typename T>
class CircularBuffer {
public:
    CircularBuffer(unsigned int minSize)
    :   mHead(0),
        mTail(0),
        mFilledSize(0)
    {
        initSize(minSize);
        mItems = new T[mLength];
    }

    ~CircularBuffer() {
        delete[] mItems;
    }


    unsigned int length() {
        return mLength;
    }

    unsigned int size() {
        return mFilledSize;
    }

    void push(T item) {
        mItems[mTail] = item;
        pushTail(1);
    }

    void push(T* items, unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
            mItems[(mTail + i) & mSizeMask] = items[i];
        }
        pushTail(n);
    }

    T& operator[](unsigned int i) {
        return mItems[(mHead + i) & mSizeMask];
    }

    void read(T* dst, unsigned int size) {
        for (unsigned int i = 0; i < size; i++) {
            dst[i] = (*this)[i];
        }
    }

    T consume() {
        pushHead(1);
        return (*this)[-1];
    }

    void consume(T* dst, unsigned int size) {
        read(dst, size);
        pushHead(size);
    }

    void pushHead(unsigned int n) {
        mHead = (mHead + n) & mSizeMask;
        mFilledSize = std::min(mFilledSize - n, mLength);
    }

    void pushTail(unsigned int n) {
        mTail = (mTail + n) & mSizeMask;
        mFilledSize = std::min(mFilledSize + n, mLength);
    }

private:
    unsigned int mLength;
    unsigned int mSizeMask;
    unsigned int mFilledSize;
    unsigned int mHead;
    unsigned int mTail;
    T* mItems;

   void initSize(unsigned int n) {
        const float nlog = log2(n);
        const unsigned int highestMaskBit = ceil(nlog);

        mLength = 1 << highestMaskBit;
        mSizeMask = 0;
        for (int i = 0; i <= highestMaskBit; i++) {
            mSizeMask += 1 << i;
        }
    }
};

#endif // _MODEM_INCLUDE_CIRCULAR_BUFFER_HPP_
