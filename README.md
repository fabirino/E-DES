# E-DES 

## Introduction
The Data Encryption Standard (DES) algorithm represents a milestone in the world of symmetric block ciphers. However, because of the time it was conceived, it has become obsolete due to two main factors: slowness and small key size. The slowness is mainly due to the bit operations performed in software, namely permutations. In addition, the original key size of only 56 bits was considered by many to be insufficient at the time the algorithm was standardized.

In this project, we aim to explore a variant of DES, called E-DES. This variant uses fewer operations to implement a cipher similar to DES, and is composed exclusively of Feistel Networks and S-Boxes (Substitution Boxes). S-Boxes are common components in many ciphers, and DES is no exception. However, DES uses static S-Boxes, a choice that often raises concerns about possible hidden cryptanalysis traps. In E-DES, we will use variable, key-dependent S-Boxes. In addition, E-DES will employ longer keys, with 256 bits, in order to improve security and cryptanalysis resistance. 


## Run the program
The program can be run in 2 different languages (Python and C). There are 3 different programs for each language:
- encrypt
- decrypt
- speed

In order to run the C files use the correspondent executable files or simple compile them with the makefile given in the repository. The make file compiles all of the C files and deletes the correspondent *.o files.

The encrypt and decrypt files require a 32 bytes key given in arguments of the execution call. A key with a different size or no key at all will raise an error that ends the program.

The speed file requires a number that corresponds to the measurement that will be done:
- 0 - Time of encryption for E-DES 
- 1 - Time of decryption for E-DES 
- 3 - Time of encryption for DES 
- 2 - Time of decryption for DES 

### C
**Cipher**
``` shell
./encrypt key < ./inputs/example2.txt > ./outputs/ciphertext2.txt 
```
**Decipher**
``` shell
./decrypt key < ./outputs/ciphertext2.txt  > ./outputs/plaintext2.txt
```
``` shell
./speed option
```
### Python
**Cipher**
``` shell
python3 encrypt.py < ./inputs/example1.txt > ./outputs/ciphertext3.txt
```
**Decipher**
``` shell
python3 encrypt.py < ./outputs/ciphertext3.txt > ./outputs/plaintext3.txt
```
``` shell
python3 speed.py option
```

## Work done by
- Fábio Santos
- Rodrigo Marques