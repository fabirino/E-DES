FLAGS	= -Wall -g
CC	= gcc

PROG1 = encrypt
OBJS1 = encrypt.o sbox.o

PROG2 = decrypt
OBJS2 = decrypt.o sbox.o

###############################################
# $@ nome do target

all: ${PROG1} ${PROG2} clean

${PROG1}: ${OBJS1}
	${CC} ${FLAGS} ${OBJS1} -o $@

${PROG2}: ${OBJS2}
	${CC} ${FLAGS} ${OBJS2} -o $@

.PHONY: clean
clean:
	rm -f ${OBJS1} ${OBJS2}

###############################################

sbox.o: sbox.h sbox.c

# Encrypt
encryption.o: encrypt.c sbox.c

encrypt: encrypt.o sbox.o

# Decrypt
decryption.o: decrypt.c sbox.c

decrypt: decrypt.o sbox.o