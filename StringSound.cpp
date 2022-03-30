// Copyright [2020] <Vien Tran>
#include "./StringSound.h"

#include <vector>

StringSound::StringSound(double frequency) {
    if (frequency == 0) {
        throw std::runtime_error("Math error: Attempted to divide by Zero\n");
    }

    auto N = ceil(SAMPLES_PER_SEC / frequency);
    _cb = new CircularBuffer(N);
}

StringSound::StringSound(std::vector<sf::Int16> init) {
    auto cap = init.size();
    _cb = new CircularBuffer(cap);
    for (auto i = 0; i < cap; i++) {
        _cb->enqueue(init[i]);
    }
}

StringSound::~StringSound(void) {
    delete _cb;
}

void StringSound::pluck(void) {
    if (!_cb->isEmpty()) {
        _cb->empty();
    }

    unsigned int seed =
    std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g1(seed);
    std::uniform_int_distribution<int16_t> rVal(-32767, 32767);

    for (auto i = 0; i < _cb->getCapacity(); i++) {
        _cb->enqueue(rVal(g1));
    }
}

void StringSound::tic(void) {
    auto firstSample = _cb->dequeue();
    auto secondSample = sample();
    _cb->enqueue(0.996 * (0.5*(firstSample + secondSample)));
    _time++;
}

sf::Int16 StringSound::sample(void) {
    sf::Int16 _sample = _cb->peek();
    return _sample;
}

int StringSound::getTime(void) {
    return _time;
}
