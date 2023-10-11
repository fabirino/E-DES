#include "sbox.h"

void sbox_write(SBox *sbox, uint8_t array[256]){
    for (int i = 0; i < 256; i++) {
        sbox->s[i] = array[i];
    }
}