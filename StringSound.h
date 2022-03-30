// Copyright [2022] <Vien Tran>
#ifndef PS4_PS4B_STRINGSOUND_H_
#define PS4_PS4B_STRINGSOUND_H_

#include "CircularBuffer.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <cmath>
#include <random>
#include <ctime>

#define SAMPLES_PER_SEC 44100

class StringSound {
 public:
    // create a guitar string sound of the given frequency
    // using the sampling rate of 44,100
    explicit StringSound(double frequency);
    // craete a guitar string with size
    // and initial values are given by the vector
    explicit StringSound(std::vector<sf::Int16> init);

    StringSound(const StringSound &obj) = delete;  // no copy const

    ~StringSound();

    // pluck the guitar string by replacing the buffer
    // with random values, representing white noise
    void pluck();
    // advance the simulation one time step
    void tic();

    // return the current sample;
    sf::Int16 sample();
    // return the number of times tic was called so far
    int getTime();

 private:
    CircularBuffer * _cb;
    int _time;
};

#endif  // PS4_PS4B_STRINGSOUND_H_
