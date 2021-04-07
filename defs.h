//
// Created by Harry Wright on 07/04/2021.
//

#ifndef SKAK_DEFS_H
#define SKAK_DEFS_H

#include "stdio.h"

typedef unsigned long long U64;

#define INIT_U64 1ULL

#define SKLogLine printf("\n")
#define SKLog(format, ...) printf(format, ##__VA_ARGS__)

#ifndef DEBUG
#define SKDebugLog(format, ...)
#else
#define SKDebugLog(format, ...) SKLog(format, ##__VA_ARGS__)
#endif

#endif //SKAK_DEFS_H
