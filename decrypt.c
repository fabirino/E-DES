/**
 * @file decrypt.c
 * @brief Decrypts a message using the E-DES algorithm
 * @author Fábio Santos 1188351
 * @author Rodrigo Marques 118587
 * @date 05/11/2023
*/

#include "E-DES.h"
#include "sboxExample.h"

int main(int argc, char **argv) {

    // Get the arguments of the program
    if (argc != 2) {
        printf("Usage: ./decrypt <32-characters key>\n");
        return 1;
    }

    char* password = argv[1];
    // char *password = "abcdefghijklmnopqrstuvxyz1234567";

    // Validate the arguments
    if (strlen(password) != PW_LEN) {
        // printf("LEN: %d\n", strlen(password));
        printf("Key must be 32 characters long\n");
        return 1;
    }


    // Create the S-Boxes
    SBox SBoxes[16];
    create_SBoxes(SBoxes, password);
    // sbox_write(&SBoxes[0], SBox_01);
    // sbox_write(&SBoxes[1], SBox_02);
    // sbox_write(&SBoxes[2], SBox_03);
    // sbox_write(&SBoxes[3], SBox_04);
    // sbox_write(&SBoxes[4], SBox_05);
    // sbox_write(&SBoxes[5], SBox_06);
    // sbox_write(&SBoxes[6], SBox_07);
    // sbox_write(&SBoxes[7], SBox_08);
    // sbox_write(&SBoxes[8], SBox_09);
    // sbox_write(&SBoxes[9], SBox_10);
    // sbox_write(&SBoxes[10], SBox_11);
    // sbox_write(&SBoxes[11], SBox_12);
    // sbox_write(&SBoxes[12], SBox_13);
    // sbox_write(&SBoxes[13], SBox_14);
    // sbox_write(&SBoxes[14], SBox_15);
    // sbox_write(&SBoxes[15], SBox_16);

    // // Test variables
    // uint8_t teste[] = {0x3c, 0x58, 0x2b, 0x44, 0x04, 0x4b, 0x5f, 0x1c,
    //                    0x3d, 0x55, 0x20, 0x41, 0x06, 0x4e, 0x69, 0x64,
    //                    0x3d, 0x59, 0x2b, 0x47, 0x05, 0x45, 0x58, 0x19,
    //                    0x3c, 0x5b, 0x21, 0x43, 0x07, 0x4c, 0x6c, 0x63,
    //                    0x3a, 0x53, 0x19, 0x48, 0x0c, 0x6a, 0x60, 0x7c,
    //                    0x3f, 0x15, 0x18, 0x62, 0x1d, 0x0c, 0x7f, 0x62,
    //                    0x3e, 0x28, 0x12, 0x7e, 0x12, 0x7a, 0x63, 0x7c,
    //                    0x02, 0x6d, 0x16, 0x4b, 0x0d, 0x6a, 0x26, 0x6c};

    // int input_len = sizeof(teste);
    // uint8_t decipher[input_len];

    // // Decrypt the message
    // feistel_networks_decrypt(SBoxes, teste, decipher, input_len);
    // for (int i = 0; i < input_len; i++) {
    //     printf("%02x ", decipher[i]);
    //     if (i % 8 == 7) {
    //         printf("\n");
    //     }
    // }


    // Read the input in bytes
    uint64_t bytes_read;
    uint8_t *input_bytes = NULL;
    input_bytes = read_msg_bytes(&bytes_read);
    bytes_read = bytes_read - (bytes_read % 8); // Remove some garbage
    
    if(bytes_read == 0){
        printf("Error reading input\n");
        return 1;
    }

    // Decrypt
    uint8_t *output = (uint8_t *)malloc(bytes_read * sizeof(uint8_t));
    feistel_networks_decrypt(SBoxes, input_bytes, output, bytes_read);


    // Remove the padding
    remove_padding(output, &bytes_read);
    free(input_bytes);

    // Convert the bytes to char
    char output_str[bytes_read];
    bytes_to_char(output, output_str, bytes_read);
    free(output);
    printf("%s", output_str);

    return 0;
}