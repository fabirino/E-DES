#include "sbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PW_LEN 32

// ============================================================
// ======================== GERAL =============================
// ============================================================


void shuffle(uint8_t arr[], int seed);

void char_to_bytes(char *input, uint8_t *output, int len);

void read_msg(char **msg);

void create_SBoxes(SBox *SBoxes, uint8_t *passwordBytes);

void f_SBox(SBox SBox, uint8_t input[4], uint8_t output[4]);

// ============================================================
// ======================== ENCRYPT ===========================
// ============================================================

void feistel_networks_block(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);

void feitel_networks(SBox *SBoxes, uint8_t *input, uint8_t *output, int input_len);

// ============================================================
// ======================== DECRYPT ===========================
// ============================================================

void feistel_networks_block_decrypt(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);

void feitel_networks_decrypt(SBox *SBoxes, uint8_t *input, uint8_t *output, int input_len);

