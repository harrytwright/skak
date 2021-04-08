//
// Created by Harry Wright on 07/04/2021.
//

#include "init.h"

#include "hash+private.h"
#include "bitboards+private.h"
#include "board+private.h"

void initialise() {
    hash_keys_init();
    bit_mask_init();
    board_init();
}
