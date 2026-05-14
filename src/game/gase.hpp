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
    // Volume is constant and = 1
    // Required 2 from 3 paramters: mass, presure, temperature
    float pressure;
    float temperature;

    // Constants
    static constexpr float pressureKoef = 0.1;
    static constexpr float temperatureKoef = 0.1;

public:
    Gase();
    void reset();

    void applyPressure(float pressure);
    void applyTemperature(float changeTemperature);
    void heatUpTo(Gase& dest, float targetTemp) const;
    float getPressure() const;
    float getTemperature() const;

    // Interact between 2 cell with saving to new place
    void exchange(const Gase& src2, Gase& dst1, Gase& dst2) const;

    // Take air from current cell to outlet
    void vent(const Gase& srcOut, Gase& dstIn, Gase& dstOut, float power) const;

    // Drawing
    void blitThermal(const Window& window, SDL_FRect rect) const;
    void blitPressure(const Window& window, SDL_FRect rect) const;
};
