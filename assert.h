//
// Created by Harry Wright on 07/04/2021.
//

#ifndef SKAK_ASSERT_H
#define SKAK_ASSERT_H

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)                                      \
    if (!(n)) {                                        \
        printf("[%s] - failed ", #n);                  \
        printf("@ line %d in %s", __LINE__, __FILE__); \
        exit(1);                                       \
    }
#endif

#endif  // SKAK_ASSERT_H
