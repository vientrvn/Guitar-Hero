// Copyright [2020] <Vien Tran>

#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include <utility>
#include <memory>
#include <vector>

#include "CircularBuffer.h"
#include "StringSound.h"

#define NUM_KEY 37

int main() {
    sf::Image image;
    if (!image.loadFromFile("background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    sf::Vector2u size = image.getSize();
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Guitar Simulator");

    double freq;
    // sf::Int16 vector, holds the audio sample stream generated by StringSound
    std::vector<std::vector<sf::Int16>> samplesV;
    // a vector of 37 SoundBuffers
    std::vector<std::shared_ptr<sf::SoundBuffer>> soundBufferVec;
    // a vector of 37 Sounds
    std::vector<sf::Sound> soundVec;

    for (auto i = 0; i < NUM_KEY; i++) {
        freq = ceil(440.0 * pow(2.0, (i-24.0)/12.0));
        std::vector<sf::Int16> samples;

        StringSound ss(freq);
        auto makeSamples = [](StringSound &ss) -> std::vector<sf::Int16> {
            std::vector<sf::Int16> samples;

            ss.pluck();
            int duration = 8;  // seconds
            for (auto i = 0; i < SAMPLES_PER_SEC * duration; i++) {
                ss.tic();
                samples.push_back(ss.sample());
            }
            return samples;
        };
        samples = makeSamples(ss);
        samplesV.push_back(samples);
    }

    for (auto i = 0; i < NUM_KEY; i++) {
        std::shared_ptr<sf::SoundBuffer> soundBuffer =
        std::make_shared<sf::SoundBuffer> ();

        if (!soundBuffer->loadFromSamples(&samplesV[i][0],
        samplesV.at(i).size(), 2, SAMPLES_PER_SEC)) {
           throw std::runtime_error("SoundBuffer failed to load from samples.");
        }
        soundBufferVec.push_back(soundBuffer);
    }

    for (auto i = 0; i < NUM_KEY; i++) {
        sf::Sound sounds;
        sounds.setBuffer(*soundBufferVec[i]);
        soundVec.push_back(sounds);
    }

    std::string keys = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
    std::map<char, int> key_map;
    int i = 0;
    for (auto &c : keys) {
        key_map.insert(std::pair<char, int>(c, i));
        i++;
    }

    size_t isFound = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            isFound = keys.find(event.text.unicode);
            if (isFound != std::string::npos) {
                soundVec[key_map.find(event.text.unicode)->second].play();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}