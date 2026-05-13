/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"
#include "navigation.hpp"


//
class Cell {
 public:
    // Masks for state interaction
    typedef Uint8 CellState;  // Type for storing cell state

    // Possible states of cell
    enum State : CellState {
        // Hollow, air can came
        Air    = 0b00000,
        Heater = 0b00100,

        // Filled, air can't came throw
        Wall      = 0b10000,
        // Vent types (0b101)
        VentUp    = 0b10100,
        VentRight = 0b10101,
        VentDown  = 0b10110,
        VentLeft  = 0b10111,

        // Special
        Buldozer  = 0b11111111,
    };

 protected:
    // State defines as 1 bit for air throwput, 2 bits for type, 2 bits for rotation
    static const CellState wallMask     = 0b10000;
    static const CellState typeMask     = 0b01100;
    static const CellState stateMask    = 0b01100;
    static const CellState rotationMask = 0b10011;

    // Constants
    static constexpr float pressureKoef = 0.1;
    static constexpr float temperatureKoef = 0.1;
    static constexpr float heatTarget = 200.0;

    // Variaables per cell
    Uint8 state = Air;
    float pressure;
    float temperature;

    // Check state
    bool isWall() const;  // Return, if air can't came throw
    bool isVent() const;  // Return, if this is vent

 public:
    Cell();
    void reset();

    // Interactions
    void setState(int state);
    void applyPressure(float pressure);
    void applyTemperature(float temperature);
    float getPressure() const;
    float getTemperature() const;

    // Every cycle update
    void exchange(const Cell& src2, Cell& dst1, Cell& dst2) const;  // Interact between 2 cell with saving to new place
    void update();

    // Drawing
    void blitNormal(const Window& window, SDL_FRect rect) const;
    void blitThermal(const Window& window, SDL_FRect rect) const;
    void blitPressure(const Window& window, SDL_FRect rect) const;
};
