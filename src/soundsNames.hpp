/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"


// Check, if use mixer and preload sounds
#if (USE_SDL_MIXER) && (PRELOAD_SOUNDS)


// Names of sound effects
enum class Sounds : unsigned {
    // Game part
    Turn,
    Reset,

    // Global counter of all loaded sounds
    Count,
};

// File names of the corresponding sounds
extern const char* soundsFilesNames[unsigned(Sounds::Count)];

#endif  // (USE_SDL_MIXER) && (PRELOAD_SOUNDS)
