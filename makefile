FLAGS	= -Wall -g
CC	= gcc
LIBS = -lssl -lcrypto

PROG1 = encrypt
OBJS1 = encrypt.o sbox.o e-des.o

PROG2 = decrypt
OBJS2 = decrypt.o sbox.o e-des.o

PROG3 = speed
OBJS3 = speed.o sbox.o e-des.o

###############################################
# $@ nome do target

all: ${PROG1} ${PROG2} ${PROG3} clean

${PROG1}: ${OBJS1}
	${CC} ${FLAGS} ${OBJS1} -o $@ ${LIBS}

${PROG2}: ${OBJS2}
	${CC} ${FLAGS} ${OBJS2} -o $@ ${LIBS}

${PROG3}: ${OBJS3}
	${CC} ${FLAGS} ${OBJS3} -o $@ ${LIBS} -lrt

.PHONY: clean
clean:
	rm -f ${OBJS1} ${OBJS2} ${OBJS3}

###############################################

sbox.o: sbox.h sbox.c

e-des.o: e-des.h e-des.c


# Encrypt
encryption.o: encrypt.c sbox.c

encrypt: encrypt.o sbox.o e-des.o

# Decrypt
decryption.o: decrypt.c sbox.c

decrypt: decrypt.o sbox.o e-des.o

# Speed

speed.o: speed.c sbox.c

speed: speed.o sbox.o e-des.o