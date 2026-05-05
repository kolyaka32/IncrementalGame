/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/preloaded/loader/loader.hpp"
#include "data/libraries.hpp"
#include "data/initFile.hpp"
#include "cycles/selectCycle.hpp"  // Start game cycle
#include "internet/internet.hpp"


// Initialasing global objects in correct order
// Logger
#if (CHECK_ALL)
std::ofstream logFile{"log.txt"};
#endif

// All side libries
Libraries libraries{};

#if (PRELOAD_DATA)
const DataLoader dataLoader{};
#endif

#if (USE_SDL_MIXER) && (PRELOAD_MUSIC)
MusicData music{};
#endif

#if (USE_SDL_MIXER) && (PRELOAD_SOUNDS)
SoundsData sounds{};
#endif

#if (USE_SDL_NET)
Internet internet{};
#endif

// Main function
int main(int argv, char **args) {
    // Loading/unloading all parameters for game
    #if (USE_SETTING_FILE)
    InitFile initFile{};
    #endif

    // Creating main window
    Window window{600, 600, {"Billiard", "Бильярд", "Billardkugel", "Більярд"}};

    // Running menu
    CycleTemplate::runCycle<SelectCycle>(window);

    // Successful end of program
    return 0;
}
