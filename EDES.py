"""!
@file EDES.py
@brief This file contains the implementation of the EDES algorithm.
@author Fábio Santos 118351
@author Rodrigo Marques 118587
@date 05/01/2023
"""

import sys
import hashlib

PW_LEN = 32

# ============================================================
# ======================== GERAL =============================
# ============================================================
#make a documentation for this function


def sha256(input):
    '''!
    @brief This function returns the sha256 of the input.
    @param input The input to be hashed.
    '''
    sha256 = hashlib.sha256()
    sha256.update(input.encode("utf-8"))
    sha256_bytes = sha256.digest()
    sha256_bytearray = bytearray(sha256_bytes)

    return sha256_bytearray


def sha256_bytearray(byte_array):
    '''!
    @brief This function returns the sha256 of the input.
    @param input The input to be hashed.
    '''

    sha256 = hashlib.sha256()
    sha256.update(byte_array)
    sha256_bytes = sha256.digest()
    sha256_bytearray = bytearray(sha256_bytes)

    return sha256_bytearray


def read_to_bytearray():
    '''!
    @brief This function reads the input from stdin into a bytearray.
    @return The bytearray containing the input and the number of bytes read.
    '''

    try:
        # Read input from stdin into a bytearray
        # data = bytearray(sys.stdin.buffer.read())
        data = bytearray(sys.stdin.buffer.read())
        bytes_read = len(data)

        return data, bytes_read
    except Exception as e:
        print("An error occurred:", e)
        return None, 0


def add_padding(input, bytes_read):
    '''!
    @brief This function adds padding to the input.
    @param input The input to be padded.
    @param bytes_read The number of bytes read from stdin.
    @return The padded input.
    '''

    if (bytes_read % 8 != 0):
        padding_size = 8 - (bytes_read % 8)
        for _ in range(padding_size):
            input.append(padding_size)
    else:
        for _ in range(8):
            input.append(0x08)
    return input


def remove_padding(input):
    '''!
    @brief This function removes the padding from the input.
    @param input The input to be unpadded.
    @return The unpadded input.
    '''

    padding_size = int(input[-1])
    return input[:-padding_size]


def create_SBoxes(password):
    '''!
    @brief This function creates the SBoxes.
    @param password The password to be used to create the SBoxes.
    @return The SBoxes.
    '''

    # Init the SBoxes
    SBoxes = []
    for _ in range(16):
        SBoxes.append(bytearray([j for j in range(256)]))

    hash = sha256(password)

    # Shuffle the SBoxes
    for i in range(16):
        for j in range(256):
            value = hash[j % 32]
            aux = SBoxes[i][j]
            SBoxes[i][j] = SBoxes[i][value]
            SBoxes[i][value] = aux
        hash = sha256_bytearray(hash)

    return SBoxes


def f_SBox(SBox, input):
    '''!
    @brief This function applies the SBox to the input.
    @param SBox The SBox to be used.
    @param input The input to be used.
    @return The output of the SBox.
    '''

    index = input[3] % 256
    output = [SBox[index]]

    index = (index + input[2]) % 256
    output.append(SBox[index])

    index = (index + input[1]) % 256
    output.append(SBox[index])

    index = (index + input[0]) % 256
    output.append(SBox[index])

    return output


# ============================================================
# ======================== ENCRYPT ===========================
# ============================================================


def feistel_networks_block(SBoxes, block):
    '''!
    @brief This function applies the feistel networks to a block.
    @param SBoxes The SBoxes to be used.
    @param block The block to be used.
    @return ciphered block.
    '''

    output = bytearray(8)
    block_left = block[:4]
    block_right = block[4:]

    for i in range(16):
        block_left_next = block_right[:]
        block_right_next = bytearray(4)

        block_right_next = f_SBox(SBoxes[i], block_right)
        for j in range(4):
            block_right_next[j] = block_right_next[j] ^ block_left[j]

        block_left = block_left_next[:]
        block_right = block_right_next[:]

    output[:4] = block_left[:]
    output[4:] = block_right[:]

    return output


def feistel_networks(Sboxes, input):
    '''!
    @brief This function applies the feistel networks to the input.
    @param SBoxes The SBoxes to be used.
    @param input The input to be used.
    @return ciphered input.
    '''

    num_blocks = int(len(input) / 8)
    output = bytearray(len(input))
    for i in range(num_blocks):
        block = input[i*8: i*8+8]
        output[i*8: i*8+8] = feistel_networks_block(Sboxes, block)

    return output


# ============================================================
# ======================== DECRYPT ===========================
# ============================================================


def feistel_networks_block_decrypt(SBoxes, block):
    '''!
    @brief This function applies the feistel networks to a block to decrypt it
    @param SBoxes The SBoxes to be used.
    @param block The block to be used.
    @return deciphered block.
    '''

    output = bytearray(8)
    block_left = block[4:]
    block_right = block[:4]

    for i in range(15, -1, -1):
        block_left_previous = block_right[:]
        block_right_previous = bytearray(4)

        block_right_previous = f_SBox(SBoxes[i], block_right)
        for j in range(4):
            block_right_previous[j] = block_right_previous[j] ^ block_left[j]

        block_left = block_left_previous[:]
        block_right = block_right_previous[:]

    output[:4] = block_right[:]
    output[4:] = block_left[:]

    return output


def feistel_networks_decrypt(Sboxes, input):
    '''!
    @brief This function applies the feistel networks to the input to decrypt it.
    @param SBoxes The SBoxes to be used.
    @param input The input to be used.
    @return deciphered input.
    '''

    num_blocks = int(len(input) / 8)
    output = bytearray(len(input))
    for i in range(num_blocks):
        block = input[i*8: i*8+8]
        output[i*8: i*8+8] = feistel_networks_block_decrypt(Sboxes, block)

    return output
