//
// Created by Harry Wright on 07/04/2021.
//
// The masks could maybe move somewhere else, but not sure for now, maybe to
// board.{c,h}
//

#ifndef SKAK_INIT_H
#define SKAK_INIT_H

#include "defs.h"

#pragma mark - Define

#define CLEAR_BIT(bb, sq) ((bb) &= kClearMask[(sq)])
#define SET_BIT(bb, sq) ((bb) |= kSetMask[(sq)])

#pragma mark - Globals

extern U64 kSetMask[64];
extern U64 kClearMask[64];

#pragma mark - Functions

extern void initialise();

#endif  // SKAK_INIT_H
