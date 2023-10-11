// #ifdef SBOX_H
// #define SBOX_H

#include <stdint.h>

typedef struct sbox {
    uint8_t s[256];
} SBox;

void sbox_write(SBox *sbox, uint8_t array[256]);

// #endif