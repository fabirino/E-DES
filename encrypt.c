#include "E-DES.h"
#include "sboxExample.h"

int main(int argc, char **argv) {

    // TODO: Uncomment this
    // Get the arguments of the program
    // if (argc != 2) {
    //     printf("Usage: ./encrypt <32-characters key>\n");
    //     return 1;
    // }

    // char *password = argv[1];
    char *password = "abcdefghijklmnopqrstuvxyz1234567";

    // Validate the arguments
    if (strlen(password) != PW_LEN) {
        // printf("LEN: %d\n", strlen(password));
        printf("Key must be 32 characters long\n");
        return 1;
    }

    // Convert the password to bytes
    // uint8_t passwordBytes[PW_LEN];
    // char_to_bytes(password, passwordBytes, PW_LEN);
    // int seed = passwordBytes[1] ^ 0xdeadbeef;
    // shuffle(passwordBytes, PW_LEN);

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


    // Read the input in bytes
    uint64_t bytes_read;
    uint8_t *input_bytes = read_msg_bytes(&bytes_read);

    if(bytes_read == 0){
        printf("Error reading input\n");
        return 1;
    }

    // Add padding
    // bytes_read += 8 - (bytes_read % 8);
    add_padding(input_bytes, &bytes_read);

    // // Test variables
    // uint8_t teste[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //                    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //                    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    //                    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    //                    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    //                    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    //                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    //                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    // int input_len = sizeof(teste);
    // uint8_t cipher_text[input_len];

    // // Encrypt the message
    // feistel_networks(SBoxes, teste, cipher_text, input_len);
    // for (int i = 0; i < input_len; i++) {
    //     printf("%02x ", cipher_text[i]);
    //     if(i % 8 == 7){
    //         printf("\n");
    //     }
    // }

    // Encrypt
    uint8_t *cipher_text = (uint8_t *)malloc(bytes_read * sizeof(uint8_t));
    feistel_networks(SBoxes, input_bytes, cipher_text, bytes_read);
    for(int i = 0; i<bytes_read; i++){
        printf("%c", cipher_text[i]);
    }
    free(input_bytes);
    free(cipher_text);

    return 0;
}