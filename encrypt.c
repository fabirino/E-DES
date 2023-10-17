#include "E-DES.h"
#include "sboxExample.h"

int main(int argc, char **argv) {

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

    // Read the input
    char *input = NULL;
    // read_msg(&input);

    // Convert input in bytes
    // int input_len = strlen(input);
    // uint8_t input_bytes[input_len];
    // char_to_bytes(input, input_bytes, input_len);
    // uint8_t output[input_len];

    // Split input in blocks of 64 bits

    // Test variables
    uint8_t teste[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    int input_len = sizeof(teste);
    uint8_t output[input_len];


    // Encrypt the message
    feitel_networks(SBoxes, teste, output, input_len);
    for (int i = 0; i < input_len; i++) {
        printf("%02x ", output[i]);
        if(i % 8 == 7){
            printf("\n");
        }
    }

    return 0;
}