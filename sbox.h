/**
 * @file sbox.h
 * @brief Header file for sboc.c
 * @author Fábio Santos 1188351
 * @author Rodrigo Marques 118587
 * @date 05/11/2023
*/

// #ifdef SBOX_H
// #define SBOX_H

#include <stdint.h>

typedef struct sbox {
    uint8_t s[256];
} SBox;

void sbox_write(SBox *sbox, uint8_t array[256]);

// #endif