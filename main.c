//
// Created by Harry Wright on 07/04/2021.
//

#define DEBUG

#include "stdio.h"

#include "defs.h"
#include "board.h"
#include "bitboards.h"

int main() {
    initialise();

    U64 play = 0ULL;
    play |= (1ULL << SQ64(D2));
    play |= (1ULL << SQ64(E5));
    print(play);

    SKLogLine;

    return 0;
}
