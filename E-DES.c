#include "E-DES.h"

// ============================================================
// ======================== GERAL =============================
// ============================================================

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

void bytes_to_char(uint8_t *input, char *output, int len) {
    for (int i = 0; i < len; i++) {
        output[i] = (char)input[i];
    }
}

// Read the message from stdin and add padding
void read_msg(char **msg) {
    int block_size = 64;
    size_t bytes_read = 0;

    // Read size bytes from stdin
    char *buffer = NULL;
    char c;

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        buffer = (char *)realloc(buffer, (bytes_read + 1) * sizeof(char));
        buffer[bytes_read] = c;
        bytes_read++;
    }

    int padding_size = block_size - (bytes_read % block_size);

    // Copy the buffer to the input
    *msg = (char *)malloc((bytes_read + padding_size + 1) * sizeof(char));
    (*msg)[0] = '\0';
    strcat(*msg, buffer);

    // Add padding
    // TODO: fazer a excessao de quando o input e multiplo de 64 fazer um bloco so de padding
    for (int i = bytes_read; i < bytes_read + padding_size; i++) {
        (*msg)[i] = (char)padding_size;
    }
    (*msg)[bytes_read + padding_size] = '\0';
}

// TODO:
void create_SBoxes(SBox *SBoxes, uint8_t *passwordBytes) {
}

// Used to transform a 4 byte value using an S-Box
void f_SBox(SBox SBox, uint8_t input[4], uint8_t output[4]) {
    uint8_t index = input[3];
    output[0] = SBox.s[index];

    index = (index + input[2]);
    output[1] = SBox.s[index];

    index = (index + input[1]);
    output[2] = SBox.s[index];

    index = (index + input[0]);
    output[3] = SBox.s[index];
}

// ============================================================
// ======================== ENCRYPT ===========================
// ============================================================

// Encrypts a block of 64 bits
void feistel_networks_block(SBox *SBoxes, uint8_t block[8], uint8_t output[8]) {
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

    for (int i = 0; i < 16; i++) {
        // Create the next blocks
        uint8_t block_left_next[4];
        uint8_t block_right_next[4];

        // The next block left is the current block right
        for (int j = 0; j < 4; j++) {
            block_left_next[j] = block_right[j];
        }

        // The next block right is the current block left XOR result of the current block right with correspondent S-Box
        f_SBox(SBoxes[i], block_right, block_right_next);
        for (int j = 0; j < 4; j++) {
            block_right_next[j] = block_right_next[j] ^ block_left[j];
        }

        // Update the blocks
        for (int j = 0; j < 4; j++) {
            block_left[j] = block_left_next[j];
            block_right[j] = block_right_next[j];
        }
    }

    // Merge the blocks
    for (int i = 0; i < 8; i++) {
        if (i < 4) {
            output[i] = block_left[i];
        } else {
            output[i] = block_right[i - 4];
        }
    }
}

// Loops through the blocks and encrypts them
void feistel_networks(SBox *SBoxes, uint8_t *input, uint8_t *output, int input_len) {
    int num_blocks = input_len / 8;
    for (int i = 0; i < num_blocks; i++) {
        feistel_networks_block(SBoxes, &input[i * 8], &output[i * 8]);
    }
}

// ============================================================
// ======================== DECRYPT ===========================
// ============================================================

void feistel_networks_block_decrypt(SBox *SBoxes, uint8_t block[8], uint8_t output[8]) {

    // Split the block in 2 equal parts
    uint8_t block_left[4];
    uint8_t block_right[4];
    for (int i = 0; i < 8; i++) {
        // Aqui troca em relacao ao encrypt
        if (i < 4) {
            block_right[i] = block[i];
        } else {
            block_left[i - 4] = block[i];
        }
    }

    for (int i = 15; i >= 0; i--) {
        // Create the previous blocks
        uint8_t block_left_previous[4];
        uint8_t block_right_previous[4];

        // The previous block left is the current block right
        for (int j = 0; j < 4; j++) {
            block_left_previous[j] = block_right[j];
        }

        // The previous block right is the current block left XOR result of the current block right with correspondent S-Box
        f_SBox(SBoxes[i], block_right, block_right_previous);
        for (int j = 0; j < 4; j++) {
            block_right_previous[j] = block_right_previous[j] ^ block_left[j];
        }

        // Update the blocks
        for (int j = 0; j < 4; j++) {
            block_left[j] = block_left_previous[j];
            block_right[j] = block_right_previous[j];
        }
    }

    // Merge the blocks
    for (int i = 0; i < 8; i++) {
        // Aqui troca em relacao ao encrypt
        if (i < 4) {
            output[i] = block_right[i];
        } else {
            output[i] = block_left[i - 4];
        }
    }
}

void feistel_networks_decrypt(SBox *SBoxes, uint8_t *input, uint8_t *output, int input_len) {
    int num_blocks = input_len / 8;
    for (int i = num_blocks; i >= 0; i--) {
        feistel_networks_block_decrypt(SBoxes, &input[i * 8], &output[i * 8]);
    }
}