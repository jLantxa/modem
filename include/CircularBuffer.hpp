/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

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

    void push(T item) {
        mItems[mTail] = item;
        advanceTail(1);
    }

    void push(T* items, unsigned int length) {
        for (unsigned int i = 0; i < length; i++) {
            push(items[i]);
        }
    }

    T pop() {
        T& item = mItems[mHead];
        advanceHead(1);
        return item;
    }

    void pop(T* dst, unsigned int length) {
        for (unsigned int i = 0; i < length; i++) {
            dst[i] = pop();
        }
    }

    T& operator[](unsigned int i) {
        return mItems[(mHead + i) & mSizeMask];
    }

    unsigned int length() {
        return mLength;
    }

    unsigned int size() {
        return mFilledSize;
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

    void advanceHead(unsigned int n) {
        mHead = (mHead + n) & mSizeMask;
        mFilledSize = std::min(mFilledSize - n, mLength);
    }

    void advanceTail(unsigned int n) {
        mTail = (mTail + n) & mSizeMask;
        mFilledSize = std::min(mFilledSize + n, mLength);
    }
};
