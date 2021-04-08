//
// Created by Harry Wright on 07/04/2021.
//

#define DEBUG

#include "bitboards.h"
#include "board.h"
#include "defs.h"
#include "init.h"
#include "stdio.h"

int main() {
    initialise();

    int index = 0;
    U64 bb = 0ULL;

    for (index = 0; index < 64; index++) {
        SKLog("Index: %d", index);
        print_bit(kSetMask[index]);
        SKLogLine;
    }

    SKLog("A1: %d", (A1 - 21));
    //    SET_BIT(bb, (A1 - 21));
    set_bit(&bb, (A1 - 21));
    print_bit(bb);
    SKLogLine;

    return 0;
}
