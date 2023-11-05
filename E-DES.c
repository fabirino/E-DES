/**
 * @file E-DES.c
 * @brief Implementation of the E-DES algorithm
 * @author Fábio Santos 1188351
 * @author Rodrigo Marques 118587
 * @date 05/11/2023
*/

#include "E-DES.h"

// ============================================================
// ======================== GERAL =============================
// ============================================================

void sha256(char *string, uint8_t *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, string, strlen(string));
    EVP_DigestFinal_ex(mdctx, hash, NULL);
    EVP_MD_CTX_free(mdctx);
}

void sha256_uint8(uint8_t *input, size_t input_len, uint8_t *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();

    if (mdctx == NULL) {
        printf("Error in sha256\n");
        return;
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1 ||
        EVP_DigestUpdate(mdctx, input, input_len) != 1 ||
        EVP_DigestFinal_ex(mdctx, output, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        printf("Error in sha256\n");
        return; // Hashing failed
    }

    EVP_MD_CTX_free(mdctx);
}

uint8_t *read_msg_bytes(uint64_t *bytes_read) {
    uint8_t aux;
    uint8_t *input_bytes = NULL;

    (*bytes_read) = 0;
    while (fread(&aux, sizeof(uint8_t), 1, stdin) == 1) {
        input_bytes = realloc(input_bytes, (++(*bytes_read)) * sizeof(uint8_t));
        if (!input_bytes) {
            fprintf(stderr, "Failed to realloc memory!\n");
            return NULL;
        }
        input_bytes[(*bytes_read) - 1] = aux;
    }
    return input_bytes;
}

void bytes_to_char(uint8_t *input, char *output, int len) {
    for (int i = 0; i < len; i++) {
        output[i] = (char)input[i];
    }
}

void add_padding(uint8_t *input, uint64_t *bytes_read) {

    // Add padding
    int block_size = 8;
    if ((*bytes_read) % block_size != 0) {
        // Realloc the input
        int padding_size = block_size - ((*bytes_read) % block_size);
        input = (uint8_t *)realloc(input, ((*bytes_read) + padding_size) * sizeof(uint8_t));
        // Add padding to the rest of the block
        for (int i = (*bytes_read); i < (*bytes_read) + padding_size; i++) {
            input[i] = (uint8_t)padding_size;
        }
        (*bytes_read) += padding_size;
    } else {
        // Realloc the input
        input = (uint8_t *)realloc(input, ((*bytes_read) + block_size) * sizeof(uint8_t));
        // Add another block of padding
        for (int i = (*bytes_read); i < (*bytes_read) + block_size; i++) {
            input[i] = (uint8_t)block_size;
        }
        (*bytes_read) += block_size;
    }
}

void remove_padding(uint8_t *input, uint64_t *len) {
    
    // int padding_size = input[len - 1] == 0 ? input[len - 2] : input[len - 1];
    uint8_t padding_size = input[(*len) - 1];
    (*len) -= padding_size;
    input[(*len) - padding_size] = '\0';
}


void read_msg(char **msg) {
    int block_size = 8;
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
    *msg = (char *)malloc((bytes_read + 1) * sizeof(char));
    (*msg)[0] = '\0';
    strcat(*msg, buffer);
    free(buffer);
}

void create_SBoxes(SBox *SBoxes, char *password) {

    // Inicialize the SBoxes
    for (int i = 0; i < 16; i++) {
        for (uint8_t j = 0x00; j < 0xff; j++) {
            SBoxes[i].s[j] = j;
        }
        SBoxes[i].s[0xff] = 0xff;
    }
    
    
    // Shuffle the SBoxes using the password
    uint8_t *hash = (uint8_t *)malloc(SHA256_DIGEST_LENGTH * sizeof(uint8_t));
    if (hash == NULL) {
        printf("Error allocating memory\n");
        return; // Memory allocation failed
    }

    sha256(password, hash);

    for (int i = 0; i < 16; i++) {

        // Shuffle the SBox
        for (int j = 0; j < 256; j++) {
            uint8_t value = hash[j % 32];

            uint8_t aux = SBoxes[i].s[j];
            SBoxes[i].s[j] = SBoxes[i].s[value];
            SBoxes[i].s[value] = aux;
        }

        // Get the next hash (hash of previous hash)
        sha256_uint8(hash, SHA256_DIGEST_LENGTH, hash);
    }
}


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


void feistel_networks(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len) {
    uint64_t num_blocks = input_len / 8;
    for (uint64_t i = 0; i < num_blocks; i++) {
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

void feistel_networks_decrypt(SBox *SBoxes, uint8_t *input, uint8_t *output, uint64_t input_len) {
    uint64_t num_blocks = input_len / 8;
    for (uint64_t i = 0; i < num_blocks; i++) {
        feistel_networks_block_decrypt(SBoxes, &input[i * 8], &output[i * 8]);
    }
}
