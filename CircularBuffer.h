// Copyright [2022] <Vien Tran>
#ifndef PS4_PS4B_CIRCULARBUFFER_H_
#define PS4_PS4B_CIRCULARBUFFER_H_

#include <stdint.h>
#include <iostream>
#include <memory>

class CircularBuffer {
 public:
    // create an empty ring buffer, with given max capacity
    explicit CircularBuffer(size_t capacity);

    size_t size();            // return number of items currently in the buffer
    bool isEmpty();           // is the buffer empty (size equals zero)?
    bool isFull();            // is the buffer full (size equals capacity)?
    void enqueue(int16_t x);  // add item x to the end
    int16_t dequeue();        // delete and return item from the front
    int16_t peek();           // return (but do not delete) item from the front
    void empty(void);         // empty the buffer

    size_t getCapacity(void) const;

 private:
    size_t cap, numItems, front;
    std::unique_ptr<int16_t[]> buffer;
};

#endif  // PS4_PS4B_CIRCULARBUFFER_H_
