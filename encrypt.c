#include "sboxExample.h"
#include "sbox.h"
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


void feistel_networks() {

}

int main(int argc, char **argv) {

    // Get the arguments of the program
    // if (argc != 2) {
    //     printf("Usage: ./encrypt <32-characters key>\n");
    //     return 1;
    // }

    // char *password = argv[1];
    char *password = "abcdefghijklmnopqrstuvwxyz123456";

    // Validate the arguments
    if (strlen(password) != PW_LEN) {
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

    
    

    return 0;
}