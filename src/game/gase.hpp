/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Class for interact with gase state and exchange
class Gase {
private:
    // Parameters of one cell of gase
    // Required 3 from 4 paramters: mass, presure, temperature, volume
    // Volume is constant and = 1
    float mass;         // kg
    float temperature;  // K

    // Constants
    static constexpr float volume = 1.0;
    static constexpr float pressureKoef = 0.01;
    static constexpr float heatCapacity = 0.1;  // J/kg/K
    static constexpr float drawTemperatureKoef = 2.5;
    static constexpr float drawPressureKoef = 100.0;

public:
    // Environment parameters
    static float globalPressure;
    static float globalTemperature;

    Gase();
    void reset();

    void addMass(float change);
    void reduceMass(float change);
    void addTemperature(float deltaTemperature);
    float getPressure() const;
    float getMass() const;
    float getTemperature() const;

    // Exchange of heat and pressure between cell with saving to new place
    void exchange(const Gase& src2, Gase& dst1, Gase& dst2) const;  // Exchange between to elements
    void exchange(Gase& dest) const;  // Exchange without affect of second part (world)

    // Take air from current cell to outlet
    void vent(const Gase& srcOut, Gase& dstIn, Gase& dstOut, float power) const;

    // Allow flow only to one side
    void exchangeValved(const Gase& src2, Gase& dst1, Gase& dst2) const;

    // Drawing
    void blitThermal(const Window& window, SDL_FRect rect) const;
    void blitPressure(const Window& window, SDL_FRect rect) const;
};
