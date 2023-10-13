#include "sbox.h"
#include "sboxExample.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PW_LEN 32

// Function to shuffle an array
void shuffle(uint8_t arr[], int seed) {
    srand(seed);
    for (int j = PW_LEN - 1; j >= 1; j--) {
        // we will get random value of i with in range 0 to j-1
        int i = rand() % j;
        // swap jth index with ith
        uint8_t temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
}

// Function to convert a char array to a byte array
void char_to_bytes(char *input, uint8_t *output, int len) {
    for (int i = 0; i < len; i++) {
        output[i] = (uint8_t)input[i];
    }
}

// TODO:
void create_SBoxes(SBox *SBoxes, uint8_t *passwordBytes) {
}

//   Used to transform a 4 byte value using an S-Box
void f_SBox(SBox SBox, uint8_t input[4], uint8_t output[4]) {
    uint8_t index = input[3];
    output[0] = SBox.s[index];

    index = (index ^ input[2]);
    output[1] = SBox.s[index];

    index = (index ^ input[1]);
    output[2] = SBox.s[index];

    index = (index ^ input[0]);
    output[3] = SBox.s[index];
}

// Encrypts a block of 64 bits
void feistel_networks(SBox *SBoxes, uint8_t block[8]) {
    // uint8_t block[8]correponde a um bloco de 64 bits / 8 bytes; cada bloco vai ter 4 carateres
    
    // Split the block in 2 equal parts
    uint8_t block_left[4];
    uint8_t block_right[4];
    for (int i = 0; i < 8; i++) {
        if (i < 4) {
            block_left[i] = block[i];
        } else {
            block_right[i - 4] = block[i];
        }
    }

    // Create the next blocks
    uint8_t block_left_next[4];
    uint8_t block_right_next[4];
    
    // The next block left is the current block right
    for (int i = 0; i < 4; i++) {
        block_left_next[i] = block_right[i];
    }

    // The next block right is the current block left XOR result of the current block right with correspondent S-Box
    f_SBox(SBoxes[0], block_right, block_right_next);
    for (int i = 0; i < 4; i++) {
        block_right_next[i] = block_right_next[i] ^ block_left[i];
    }

}

int main(int argc, char **argv) {

    // Get the arguments of the program
    if (argc != 2) {
        printf("Usage: ./encrypt <32-characters key>\n");
        return 1;
    }

    char *password = argv[1];
    // char *password = "abcdefghijklmnopqrstuvxyz1234567";

    // Validate the arguments
    if (strlen(password) != PW_LEN) {
        // printf("LEN: %d\n", strlen(password));
        printf("Key must be 32 characters long\n");
        return 1;
    }

    // Convert the password to bytes
    // FIXME: mudar o metodo de shuffle pois pode nao dar o mesmo resultado noutra linguagem de programacao
    uint8_t passwordBytes[PW_LEN];
    char_to_bytes(password, passwordBytes, PW_LEN);
    // FIXME: mudar a seed para algo mais complexo envolvendo a password e outros valores
    int seed = passwordBytes[1] ^ 0xdeadbeef;
    shuffle(passwordBytes, PW_LEN);

    // Create the S-Boxes
    SBox SBoxes[16];
    // create_SBoxes(SBoxes, passwordBytes);
    sbox_write(&SBoxes[0], SBox_01);
    sbox_write(&SBoxes[1], SBox_02);
    sbox_write(&SBoxes[2], SBox_03);
    sbox_write(&SBoxes[3], SBox_04);
    sbox_write(&SBoxes[4], SBox_05);
    sbox_write(&SBoxes[5], SBox_06);
    sbox_write(&SBoxes[6], SBox_07);
    sbox_write(&SBoxes[7], SBox_08);
    sbox_write(&SBoxes[8], SBox_09);
    sbox_write(&SBoxes[9], SBox_10);
    sbox_write(&SBoxes[10], SBox_11);
    sbox_write(&SBoxes[11], SBox_12);
    sbox_write(&SBoxes[12], SBox_13);
    sbox_write(&SBoxes[13], SBox_14);
    sbox_write(&SBoxes[14], SBox_15);
    sbox_write(&SBoxes[15], SBox_16);

    // Encrypt the message

    return 0;
}