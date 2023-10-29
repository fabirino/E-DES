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

    # teste = bytearray([0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    #                0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    #                0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    #                0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    #                0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    #                0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    #                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    #                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01])
    # input_len = len(teste)
    

    # # Cipher the message
    # cipher_text = EDES.feistel_networks(SBoxes, teste)
    
    # for i in range(input_len):
    #     print(hex(cipher_text[i]), end=" ")
    #     if(i % 8 == 7):
    #         print()

    # Read input from stdin into a bytearray
    input, bytes_read = EDES.read_to_bytearray()
    
    if(bytes_read == 0):
        print("No input data")
        sys.exit(1)

    # Add padding
    input = EDES.add_padding(input, bytes_read)

    # Cipher the message
    cipher_text = EDES.feistel_networks(SBoxes, input).decode('utf-8')
    for i in range(len(cipher_text)):
        print(cipher_text[i], end="")
    


    