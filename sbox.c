/**
 * @file sbox.c
 * @brief Writes the SBoxes with the given array of bytes
 * @author Fábio Santos 1188351
 * @author Rodrigo Marques 118587
 * @date 05/11/2023
*/

#include "sbox.h"

void sbox_write(SBox *sbox, uint8_t array[256]){
    for (int i = 0; i < 256; i++) {
        sbox->s[i] = array[i];
    }
}