#include "sbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#define PW_LEN 32

// ============================================================
// ======================== GERAL =============================
// ============================================================

void sha256(char *string, uint8_t *hash);

void bytes_to_char(uint8_t *input, char *output, int len);

void read_msg(char **msg);

uint8_t *read_msg_bytes(uint64_t *bytes_read);

void create_SBoxes(SBox *SBoxes, char *password);

void f_SBox(SBox SBox, uint8_t input[4], uint8_t output[4]);

void add_padding(uint8_t *input, uint64_t *bytes_read);

void remove_padding(uint8_t *input, uint64_t len);

// ============================================================
// ======================== ENCRYPT ===========================
// ============================================================

void feistel_networks_block(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);

void feistel_networks(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len);

// ============================================================
// ======================== DECRYPT ===========================
// ============================================================

void feistel_networks_block_decrypt(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);

void feistel_networks_decrypt(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len);


