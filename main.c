//
// Created by Harry Wright on 07/04/2021.
//

#define DEBUG

#include "board.h"
#include "stdio.h"

int main() {
    initialise();

    for (int index = 0; index < BOARD_MAX_LENGTH; ++index) {
        if (index % 10 == 0) printf("\n");
        printf("%5d", SQ_120_TO_64[index]);
    }

    printf("\n");

    for (int index = 0; index < STD_BOARD_LENGTH; ++index) {
        if (index % 8 == 0) printf("\n");
        printf("%5d", SQ_64_TO_120[index]);
    }

    return 0;
}
