//
// Created by Harry Wright on 07/04/2021.
//

#include "board.h"

int SQ_120_TO_64[BOARD_MAX_LENGTH];
int SQ_64_TO_120[STD_BOARD_LENGTH];

void init_array_120_64() {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;

    for (index = 0; index < BOARD_MAX_LENGTH; ++index) {
        SQ_120_TO_64[index] = 65;
    }

    for (index = 0; index < 64; ++index) {
        SQ_64_TO_120[index] = 120;
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            SQ_64_TO_120[sq64] = sq;
            SQ_120_TO_64[sq] = sq64;
            sq64++;
        }
    }
}

void initialise() {
    init_array_120_64();
}