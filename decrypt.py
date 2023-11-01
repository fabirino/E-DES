import sys
import EDES
import sboxExample

if __name__ == "__main__":

    # TODO: descomentar

    # Get the arguments of the program
    # if(len(sys.argv) != 2):
    #     print("Usage: python3 encrypt.py <message>")
    #     sys.exit(1)

    # password = sys.argv[1]
    password = "abcdefghgijklmnopqrstuvxz1234567"

    # Validate the arguments
    if (len(password) != EDES.PW_LEN):
        print("Key must have 32 characters")
        sys.exit(1)

    # TODO:
    # Convert the password to bytes
    password_bytes = EDES.char_to_bytes(password)
    # pw_shuffled = EDES.suffle(password_bytes)

    # Create SBoxes
    # SBoxes = EDES.create_SBoxes(pw_shuffled)
    SBoxes = sboxExample.load_SBoxes()

    # teste = bytearray([0x3c, 0x58, 0x2b, 0x44, 0x04, 0x4b, 0x5f, 0x1c,
    #                    0x3d, 0x55, 0x20, 0x41, 0x06, 0x4e, 0x69, 0x64,
    #                    0x3d, 0x59, 0x2b, 0x47, 0x05, 0x45, 0x58, 0x19,
    #                    0x3c, 0x5b, 0x21, 0x43, 0x07, 0x4c, 0x6c, 0x63,
    #                    0x3a, 0x53, 0x19, 0x48, 0x0c, 0x6a, 0x60, 0x7c,
    #                    0x3f, 0x15, 0x18, 0x62, 0x1d, 0x0c, 0x7f, 0x62,
    #                    0x3e, 0x28, 0x12, 0x7e, 0x12, 0x7a, 0x63, 0x7c,
    #                    0x02, 0x6d, 0x16, 0x4b, 0x0d, 0x6a, 0x26, 0x6c])
    
    # input_len = len(teste)

    # # Encypt the message
    # plaintext = EDES.feistel_networks_decrypt(SBoxes, teste)

    # for i in range(input_len):
    #     print(hex(plaintext[i]), end=" ")
    #     if(i % 8 == 7):
    #         print()

    # Read input from stdin into a bytearray
    input, bytes_read = EDES.read_to_bytearray()

    if(bytes_read == 0):
        print("No input data")
        sys.exit(1)

    # Decipher the message
    output = EDES.feistel_networks_decrypt(SBoxes, input)

    # Remove padding
    output = EDES.remove_padding(output).decode("utf-8")

    # Print the output
    for i in range(len(output)):
        print(output[i], end="")
