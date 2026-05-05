/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "soundsNames.hpp"


// Check, if use mixer and preload sounds
#if (USE_SDL_MIXER) && (PRELOAD_SOUNDS)


// File names of the corresponding sounds
const char* soundsFilesNames[unsigned(Sounds::Count)] = {
    // Game part
    "snd/turn.wav",
    "snd/reset.wav",
};

#endif  // (USE_SDL_MIXER) && (PRELOAD_SOUNDS)
