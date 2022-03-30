// Copyright [2022] <Vien Tran>
#include "./CircularBuffer.h"
#include <memory>

CircularBuffer::CircularBuffer(size_t capacity) {
    if (capacity < 1) {
        throw std::invalid_argument
        (" CircularBuffer constructor: capacity must be greater than zero.");
    }
    buffer = std::make_unique<int16_t[]>(capacity);
    cap = capacity;
    numItems = 0;
    front = 0;
}

size_t CircularBuffer::size() {
    return numItems;
}

bool CircularBuffer::isEmpty(void) {
    if (numItems == 0) {
        return true;
    }
    return false;
}

bool CircularBuffer::isFull(void) {
    if (numItems == cap) {
        return true;
    }
    return false;
}

void CircularBuffer::enqueue(int16_t x) {
    if (isFull()) {
        throw std::runtime_error("enqueue: can't enqueue to a full ring");
    }

    size_t end = (front+numItems) % cap;
    buffer[end] = x;
    numItems++;
}

int16_t CircularBuffer::dequeue(void) {
    if (isEmpty()) {
        throw std::runtime_error("dequeue: can't dequeue from an empty ring");
    }
    int16_t temp = buffer[front++];
    front %= cap;
    numItems--;
    return temp;
}

int16_t CircularBuffer::peek(void) {
    if (isEmpty()) {
        throw std::runtime_error("peek: can't peek from an empty ring");
    }

    return buffer[front];
}

void CircularBuffer::empty(void) {
    front = 0;
    numItems = 0;
}

size_t CircularBuffer::getCapacity(void) const {
    return cap;
}
