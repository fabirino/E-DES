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

/**
* Converts bytes to char
* Params: uint8_t input, char output, int len
* Output: output
*/
void bytes_to_char(uint8_t *input, char *output, int len);


/**
* Reads message from stdin and adds padding
* Params: char msg
* Output: msg
*/
void read_msg(char **msg);


/**
* Reads message bytes
* Params: uint64_t bytes_read
* Returns: input_bytes
*/
uint8_t *read_msg_bytes(uint64_t *bytes_read);


/**
* Creates SBoxes
* Params: SBox SBoxes, char password
* Output: SBoxes
*/
void create_SBoxes(SBox *SBoxes, char *password);


/**
* Used to transform a 4 byte value using an S-Box
* Params: SBox SBox, uint8_t input, uint8_t output
* Output: output
*/
void f_SBox(SBox SBox, uint8_t input[4], uint8_t output[4]);


/**
* Adds padding to an input
* Params: uint8_t input, uint64_t bytes_read
* Output: input, bytes_read
*/
void add_padding(uint8_t *input, uint64_t *bytes_read);


/**
* Removes padding from an input
* Params: uint8_t input, uint64_t len
* Output: input, len
*/
void remove_padding(uint8_t *input, uint64_t *len);

// ============================================================
// ======================== ENCRYPT ===========================
// ============================================================

/**
* Encrypts a block of 64 bits
* Params: SBox SBoxes, uint8_t block, uint8_t output
* Output: output
*/
void feistel_networks_block(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);


/**
* Loops through the blocks and encrypts them
* Params: SBox SBoxes, uint8_t input, uint8_t output, uint64_t input_len
* Output: output
*/
void feistel_networks(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len);

// ============================================================
// ======================== DECRYPT ===========================
// ============================================================


/**
* Decrypts a block of 64 bits
* Params: SBox SBoxes, uint8_t block, uint8_t output
* Output: output
*/
void feistel_networks_block_decrypt(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);


/**
* Loops through the blocks and encrypts them
* Params: SBox SBoxes, uint8_t input, uint8_t output, uint64_t input_len
* Output: output
*/
void feistel_networks_decrypt(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len);


