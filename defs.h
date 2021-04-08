//
// Created by Harry Wright on 07/04/2021.
//

#ifndef SKAK_DEFS_H
#define SKAK_DEFS_H

#include "stdio.h"

#pragma mark - Typedefs

typedef unsigned long long U64;

#pragma mark - Define

#define NAME "Skäk 0.0.1-beta.1"
#define MAX_GAME_MOVES 2048

#pragma mark - Logging

#define SKLogLine printf("\n")
#define SKLog(format, ...) printf(format, ##__VA_ARGS__)

#ifndef DEBUG
#define SKDebugLog(format, ...) printf(format, ##__VA_ARGS__)
#else
#define SKDebugLog(format, ...)
#endif

#endif  // SKAK_DEFS_H
