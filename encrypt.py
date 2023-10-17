import random

if __name__ == "__main__":
    password = "abcdefghijklmnopqrstuvxyz1234567"
    password_bytes = []
    for i in range(32):
        password_bytes.append(ord(password[i]))
        
    random.seed(password_bytes[i]^0xdeadbeef)

    for j in range(31, 1, -1):
        i = random.randint(0,2147483647) % j
        temp = password_bytes[j]
        password_bytes[j] = password_bytes[i]
        password_bytes[i] = temp
    
    for i in range(32):
        print(password_bytes[i])