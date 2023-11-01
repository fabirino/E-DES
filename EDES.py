import sys

PW_LEN = 32

# ============================================================
# ======================== GERAL =============================
# ============================================================


def suffle():
    pass


def char_to_bytes(input):
    output = []
    for i in range(len(input)):
        # output.append(format(ord(input[i]), 'x')) # 0x63
        # output.append(hex(ord(input[i])))           # 63
        output.append(bytes(ord(input[i])))         # b'c'

    return output


def read_to_bytearray():
    try:
        # Read input from stdin into a bytearray
        # data = bytearray(sys.stdin.buffer.read())
        data = bytearray(sys.stdin.buffer.read())
        bytes_read = len(data)

        return data , bytes_read
    except Exception as e:
        print("An error occurred:", e)
        return None, 0
    

def add_padding(input, bytes_read):
    # Add padding
    if(bytes_read % 8 != 0):
        padding_size = 8 - (bytes_read % 8)
        for _ in range(padding_size):
            input.append(padding_size)
    else:
        for _ in range(8):
            input.append(0x08)
    return input


def remove_padding(input):
    # Remove padding
    padding_size = int(input[-1])
    return input[:-padding_size]


# TODO: implementar
def create_SBoxes(password_bytes):
    pass


def f_SBox(SBox, input):
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
    num_blocks = int(len(input) / 8)
    output = bytearray(len(input))
    for i in range(num_blocks):
        block = input[i*8: i*8+8]
        output[i*8: i*8+8] = feistel_networks_block_decrypt(Sboxes, block)

    return output
