/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gase.hpp"


//
class Cell {
 public:
    // Masks for state interaction
    typedef Uint8 CellState;  // Type for storing cell state

    // Possible states of cell
    enum State : CellState {
        // Hollow, air can came
        Air    = 0b0000000,
        Heater = 0b0001000,

        // Filled, air can't came throw
        Wall        = 0b1000000,
        // Vent object
        VentUp      = 0b1001100,
        VentRight   = 0b1001101,
        VentDown    = 0b1001110,
        VentLeft    = 0b1001111,
        // Check valve (allow flow to one side)
        ValveUp     = 0b1010100,
        ValveRight  = 0b1010101,
        ValveDown   = 0b1010110,
        ValveLeft   = 0b1010111,
        // Coolers (cool one side and heat another)
        CoolerUp    = 0b1011100,
        CoolerRight = 0b1011101,
        CoolerDown  = 0b1011110,
        CoolerLeft  = 0b1011111,

        // Special
        Buldozer    = 0b11111111,
    };

    // Represent object (from State)
    Uint8 state = Air;

 protected:
    // State defines as 1 bit for air throwput, 3 bits for type, 2 bits for rotation
    static const CellState wallMask     = 0b1000000;  // Represent, is cell contains gase
    static const CellState typeMask     = 0b0111000;  // Represent cell type
    static const CellState rotationMask = 0b0000100;  // Represent, if cell could be rotate
    static const CellState positionMask = 0b0000011;  // Represent current rotation of cell

    // Variables per cell
    Gase gase;

    // Check state
    bool isWall() const;  // Return, if air can't came throw
    bool isRotable() const;  // Return, if part can be rotate

 public:
    Cell();
    void reset();
    void rotate();

    // Interactions
    void applyPressure(float pressure);
    void applyTemperature(float temperature);
    void heatUpTo(Cell& dest, float targetTemp) const;
    float getPressure() const;
    float getTemperature() const;

    // Every cycle update
    void exchange(const Cell& src2, Cell& dst1, Cell& dst2) const;  // Interact between 2 cell with saving to new place
    void exchange(Cell& dest) const;  // Exchange without affect of second part (world)
    void vent(const Cell& srcIn, const Cell& srcOut, Cell& dstIn, Cell& dstOut) const;

    // Drawing
    void blitNormal(const Window& window, SDL_FRect rect) const;
    void blitThermal(const Window& window, SDL_FRect rect) const;
    void blitPressure(const Window& window, SDL_FRect rect) const;
};
