#include "E-DES.h"
#include <fcntl.h>
#include <float.h>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void get_time_encrypt_EDES(SBox SBoxes[16], uint8_t *buffer, size_t buffer_size) {
    double min_time_ENCRYPT_EDES = DBL_MAX;
    double avg_time_ENCRYPT_EDES = 0.0;

    for (int i = 0; i < 100000; i++) {
        size_t size = buffer_size;

        double elapsed_time = 0; // long long int maybe
        struct timespec start, end;

        // ENCRYPT E-DES ==============================================
        // start timer
        clock_gettime(CLOCK_MONOTONIC, &start);

        add_padding(buffer, &size);
        uint8_t *cipher_text = (uint8_t *)malloc(size * sizeof(uint8_t));
        feistel_networks(SBoxes, buffer, cipher_text, size);

        // End timer
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
        if (elapsed_time < min_time_ENCRYPT_EDES) {
            min_time_ENCRYPT_EDES = elapsed_time;
        }
        avg_time_ENCRYPT_EDES += elapsed_time;
        free(cipher_text);
    }
    printf("Min Time Encrypt E-DES: %f\n", min_time_ENCRYPT_EDES);
    printf("Avg Time Encrypt E-DES: %f\n", avg_time_ENCRYPT_EDES / 100000);
}

void get_time_decrypt_EDES(SBox SBoxes[16], uint8_t *buffer, size_t buffer_size) {
    double min_time_DECRYPT_EDES = DBL_MAX;
    double avg_time_DECRYPT_EDES = 0.0;

    for (int i = 0; i < 100000; i++) {
        size_t size = buffer_size;

        double elapsed_time = 0; // long long int maybe
        struct timespec start, end;

        // DECRYPT E-DES ==============================================
        // start timer
        clock_gettime(CLOCK_MONOTONIC, &start);

        uint8_t *plain_text = (uint8_t *)malloc(size * sizeof(uint8_t));
        feistel_networks_decrypt(SBoxes, buffer, plain_text, size);
        remove_padding(plain_text, &size);

        // End timer
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
        if (elapsed_time < min_time_DECRYPT_EDES) {
            min_time_DECRYPT_EDES = elapsed_time;
        }
        avg_time_DECRYPT_EDES += elapsed_time;
        free(plain_text);
    }
    printf("Min Time Decrypt E-DES: %f\n", min_time_DECRYPT_EDES);
    printf("Avg Time Decrypt E-DES: %f\n", avg_time_DECRYPT_EDES / 100000);
}

void get_time_encrypt_DES(char *password, uint8_t *buffer, size_t buffer_size) {
    double min_time_ENCRYPT_DES = DBL_MAX;
    double avg_time_ENCRYPT_DES = 0.0;

    for (int i = 0; i < 100000; i++) {

        double elapsed_time = 0; // long long int maybe
        struct timespec start, end;
        OPENSSL_init_crypto(0, NULL);
        uint8_t iv[8];
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        clock_gettime(CLOCK_MONOTONIC, &start);
        EVP_EncryptInit_ex(ctx, EVP_des_ecb(), NULL, password, iv);
        int len;
        uint8_t *cipher_text = (uint8_t *)malloc(buffer_size * sizeof(uint8_t));
        EVP_EncryptUpdate(ctx, cipher_text, &len, buffer, sizeof(buffer));
        EVP_EncryptFinal_ex(ctx, cipher_text + len, &len);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
        if (elapsed_time < min_time_ENCRYPT_DES) {
            min_time_ENCRYPT_DES = elapsed_time;
        }
        avg_time_ENCRYPT_DES += elapsed_time;
        free(cipher_text);
    }
    printf("Min Time Encrypt DES: %f\n", min_time_ENCRYPT_DES);
    printf("Avg Time Encrypt DES: %f\n", avg_time_ENCRYPT_DES / 100000);
}

void get_time_decrypt_DES(char *password, uint8_t *buffer, size_t buffer_size) {
    double min_time_DECRYPT_DES = DBL_MAX;
    double avg_time_DECRYPT_DES = 0.0;

    for (int i = 0; i < 100000; i++) {

        double elapsed_time = 0; // long long int maybe
        struct timespec start, end;
        OPENSSL_init_crypto(0, NULL);
        uint8_t iv[8];
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        clock_gettime(CLOCK_MONOTONIC, &start);
        int len;
        uint8_t *output_DES = (uint8_t *)malloc(buffer_size * sizeof(uint8_t));
        EVP_DecryptInit_ex(ctx, EVP_des_ecb(), NULL, password, iv);
        EVP_DecryptUpdate(ctx, output_DES, &len, buffer, sizeof(buffer));
        int decrypted_len = len;
        EVP_DecryptFinal_ex(ctx, output_DES + len, &len);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
        if (elapsed_time < min_time_DECRYPT_DES) {
            min_time_DECRYPT_DES = elapsed_time;
        }
        avg_time_DECRYPT_DES += elapsed_time;
        free(output_DES);
    }

    printf("Min Time Decrypt DES: %f\n", min_time_DECRYPT_DES);
    printf("Avg Time Decrypt DES: %f\n", avg_time_DECRYPT_DES / 100000);
}

int main(int argc, char **argv) {

    // Setup
    char *password = "asdkfjaslk1111111111111111111111";
    SBox SBoxes[16];
    create_SBoxes(SBoxes, password);

    int urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd == -1) {
        perror("Error opening /dev/urandom");
        return 1;
    }

    size_t buffer_size = 4 * 1024; // 4KiB
    uint8_t *buffer = (uint8_t *)malloc(buffer_size);

    if (buffer == NULL) {
        perror("Error allocating memory");
        close(urandom_fd);
        return 1;
    }

    ssize_t bytes_read = read(urandom_fd, buffer, buffer_size);

    if (bytes_read == -1) {
        perror("Error reading from /dev/urandom");
        free(buffer);
        close(urandom_fd);
        return 1;
    }

    close(urandom_fd);

    char choice = argv[1][0];
    switch (choice) {
    case '0':
        // ENCRYPT E-DES ==============================================
        get_time_encrypt_EDES(SBoxes, buffer, buffer_size);
        break;
    case '1':
        // DECRYPT E-DES ==============================================
        get_time_decrypt_EDES(SBoxes, buffer, buffer_size);
        break;
    case '2':
        // ENCRYPT DES ==============================================
        get_time_encrypt_DES(password, buffer, buffer_size);
        break;
    case '3':
        // DECRYPT DES ==============================================
        get_time_decrypt_DES(password, buffer, buffer_size);
        break;
    default:
        printf("Usage: ./speed <choice>\n");
        printf("Choices:\n");
        printf("0: ENCRYPT E-DES\n");
        printf("1: DECRYPT E-DES\n");
        printf("2: ENCRYPT DES\n");
        printf("3: DECRYPT DES\n");
        break;
    }

    return 0;
}