"""!
@file speed.py
@brief This file contains the implementation of the speed tests for EDES and DES algorithms
@author Fábio Santos 118351
@author Rodrigo Marques 118587
@date 05/01/2023
"""

import ctypes
import platform
import sys
import EDES
from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad


class timespec(ctypes.Structure):
    _fields_ = [
        ("tv_sec", ctypes.c_long),
        ("tv_nsec", ctypes.c_long)
    ]


def get_current_time():
    tp = timespec()
    libc.clock_gettime(0, ctypes.byref(tp))
    return tp.tv_sec, tp.tv_nsec


def get_time_encrypt_EDES(SBoxes, input):
    avg_time_ENCRYPT_EDES = 0.0
    min_time_ENCRYPT_EDES = 10000.0

    for i in range(1000):
        if (i % 100 == 0):
            print(i)
        start, startn = get_current_time()

        input_padded = EDES.add_padding(input, bytes_read)
        cipher_text = EDES.feistel_networks(SBoxes, input_padded)

        end, endn = get_current_time()

        elapsed_time = (end - start) + (endn - startn) / 1000000000
        if (elapsed_time < min_time_ENCRYPT_EDES):
            min_time_ENCRYPT_EDES = elapsed_time
        avg_time_ENCRYPT_EDES += elapsed_time

    print("min_time_ENCRYPT_EDES: ", min_time_ENCRYPT_EDES)
    print("avg_time_ENCRYPT_EDES: ", avg_time_ENCRYPT_EDES/1000)


def get_time_decrypt_EDES(SBoxes, input):
    avg_time_DECRYPT_EDES = 0.0
    min_time_DECRYPT_EDES = 10000.0

    for i in range(1000):
        start, startn = get_current_time()

        ouput = EDES.feistel_networks_decrypt(SBoxes, input)
        ouput = EDES.remove_padding(ouput)

        end, endn = get_current_time()

        elapsed_time = (end - start) + (endn - startn) / 1000000000
        if (elapsed_time < min_time_DECRYPT_EDES):
            min_time_DECRYPT_EDES = elapsed_time
        avg_time_DECRYPT_EDES += elapsed_time

    print("min_time_DECRYPT_EDES: ", min_time_DECRYPT_EDES)
    print("avg_time_DECRYPT_EDES: ", avg_time_DECRYPT_EDES/1000)


def get_time_encrypt_DES(password, input):
    avg_time_ENCRYPT_DES = 0.0
    min_time_ENCRYPT_DES = 10000.0
    for i in range(1000):
        start, startn = get_current_time()

        cipher = DES.new(password, DES.MODE_ECB)
        padded_data = pad(input, DES.block_size)
        encrypted_data = cipher.encrypt(padded_data)

        end, endn = get_current_time()

        elapsed_time = (end - start) + (endn - startn) / 1000000000
        if (elapsed_time < min_time_ENCRYPT_DES):
            min_time_ENCRYPT_DES = elapsed_time
        avg_time_ENCRYPT_DES += elapsed_time

    print("min_time_ENCRYPT_DES: ", min_time_ENCRYPT_DES)
    print("avg_time_ENCRYPT_DES: ", avg_time_ENCRYPT_DES/1000)


def get_time_decrypt_DES(password, input):
    avg_time_DECRYPT_DES = 0.0
    min_time_DECRYPT_DES = 10000.0
    for i in range(1000):
        start, startn = get_current_time()

        cipher = DES.new(password, DES.MODE_ECB)
        decrypted_data = cipher.decrypt(input)
        # unpadded_data = unpad(decrypted_data, DES.block_size) # not needed

        end, endn = get_current_time()

        elapsed_time = (end - start) + (endn - startn) / 1000000000
        if (elapsed_time < min_time_DECRYPT_DES):
            min_time_DECRYPT_DES = elapsed_time
        avg_time_DECRYPT_DES += elapsed_time

    print("min_time_DECRYPT_DES: ", min_time_DECRYPT_DES)
    print("avg_time_DECRYPT_DES: ", avg_time_DECRYPT_DES/1000)


if __name__ == '__main__':

    if platform.system() == 'Linux':
        libc = ctypes.CDLL("libc.so.6")
    else:
        raise Exception("Unsupported platform")

    password = "asdkfjaslk1111111111111111111111"
    password2 = b"asdkfjas"
    SBoxes = EDES.create_SBoxes(password)

    bytes_read = 4096
    with open('/dev/urandom', 'rb') as urandom:
        input = bytearray(urandom.read(bytes_read))

    choice = sys.argv[1]

    if choice == '0':
        # ENCRYPT EDES ===============================================
        get_time_encrypt_EDES(SBoxes, input)
    elif choice == '1':
        # DECRYPT EDES ===============================================
        get_time_decrypt_EDES(SBoxes, input)
    elif choice == '2':
        # ENCRYPT DES ================================================
        get_time_encrypt_DES(password2, input)
    elif choice == '3':
        # DECRYPT DES ================================================
        get_time_decrypt_DES(password2, input)
    else:
        print("Invalid choice")
        print("Usage: python3 speed.py <choice>")
        print("Choices:")
        print("0 - ENCRYPT EDES")
        print("1 - DECRYPT EDES")
        print("2 - ENCRYPT DES")
        print("3 - DECRYPT DES")
        sys.exit(1)
