/**
 * @file E-DES.h
 * @brief Header file for E-DES.c
 * @author Fábio Santos 1188351
 * @author Rodrigo Marques 118587
 * @date 05/11/2023
*/

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

/**
* @brief hashes a string using sha256
* @param string string to be hashed
* @param hash output hash
*/
void sha256(char *string, uint8_t *hash);

/**
* @brief converts an array of bytes to an array of chars
* @param input array of bytes
* @param output array of chars
* @param len length of the input array
*/
void bytes_to_char(uint8_t *input, char *output, int len);


/**
* @brief reads message from stdin
* Receives the pointer to the message and reallocates memory everytime a new byte is read
* @param msg output message
*/
void read_msg(char **msg);


/**
* @brief reads message from stdin and stores it in an array of bytes
* @param bytes_read number of bytes read
* @return array of bytes containing the message
*/
uint8_t *read_msg_bytes(uint64_t *bytes_read);


/**
* @brief creates the SBoxes from the key
* @param SBoxes array of SBoxes
* @param password key
*/
void create_SBoxes(SBox *SBoxes, char *password);


/**
* @brief Used to transform a 4 byte array using an S-Box
* @param SBox correspondent SBox
* @param input array to be transformed
* @param output transformed array
*/
void f_SBox(SBox SBox, uint8_t input[4], uint8_t output[4]);


/**
* @brief adds padding to an input
* This function adds padding to an input so that it can be divided into blocks of 64 bits and adds the size of the padding to bytes_read
* @param input input to be padded
* @param bytes_read number of bytes read 
*/
void add_padding(uint8_t *input, uint64_t *bytes_read);


/**
* @brief removes padding from an input
* @param input input to be unpadded
* @param len length of the input
*/
void remove_padding(uint8_t *input, uint64_t *len);

// ============================================================
// ======================== ENCRYPT ===========================
// ============================================================

/**
* @brief encrypts a block of 64 bits.
* This function receives a block from the feistel_networks function and encrypts it
* @param SBoxes array of SBoxes
* @param block block to be encrypted
* @param output encrypted block
*/
void feistel_networks_block(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);


/**
* @brief loops through the blocks and encrypts them
* @param SBoxes array of SBoxes
* @param input input to be encrypted
* @param output encrypted input
* @param input_len length of the input
*/
void feistel_networks(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len);

// ============================================================
// ======================== DECRYPT ===========================
// ============================================================


/**
* @brief decrypts a block of 64 bits.
* This function receives a block from the feistel_networks_decrypt function and decrypts it
* @param SBoxes array of SBoxes
* @param block block to be decrypted
* @param output decrypted block
*/
void feistel_networks_block_decrypt(SBox *SBoxes, uint8_t block[8], uint8_t output[8]);


/**
* @brief loops through the blocks and decrypts them
* @param SBoxes array of SBoxes
* @param input input to be decrypted
* @param output decrypted input
* @param input_len length of the input
*/
void feistel_networks_decrypt(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len);


