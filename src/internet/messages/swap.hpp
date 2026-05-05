/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../data/array.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include "../../internetCodes.hpp"
#include <SDL3_net/SDL_net.h>


// Function for correct bits order to prevent wrong understanding
template <typename T>
T swapLE(T object);

#endif  // (USE_SDL_NET)
