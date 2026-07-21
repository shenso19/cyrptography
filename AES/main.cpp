#include <cstdio>
#include "aes.hpp"

void printHex(const byte* data, int len)
{
    for (int i = 0; i < len; i++)
        std::printf("%02x", data[i]);
}

int main()
{
    const byte pt[16] = {
        0x00,0x11,0x22,0x33,
        0x44,0x55,0x66,0x77,
        0x88,0x99,0xaa,0xbb,
        0xcc,0xdd,0xee,0xff
    };


    std::printf("Page\n1\nof 8\n");



    // AES-128


    std::printf("C.1 AES-128 (Nk=4, Nr=10)\n");

    const byte key128[16] = {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,
        0x0c,0x0d,0x0e,0x0f
    };

    std::printf("PLAINTEXT: ");
    printHex(pt,16);

    std::printf("\nKEY: ");
    printHex(key128,16);

    std::printf("\nCIPHER (ENCRYPT):\n");


    word w128[Nb*(10+1)];
    keyExpansion(key128,w128,4,10);

    byte ct128[16];
    cipher(pt,ct128,w128,10);


    std::printf("INVERSE CIPHER (DECRYPT):\n");

    byte dec128[16];
    invCipher(ct128,dec128,w128,10);



    // AES-192

    std::printf("C.2 AES-192 (Nk=6, Nr=12)\n");

    const byte key192[24] = {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,
        0x0c,0x0d,0x0e,0x0f,
        0x10,0x11,0x12,0x13,
        0x14,0x15,0x16,0x17
    };


    std::printf("PLAINTEXT: ");
    printHex(pt,16);

    std::printf("\nKEY: ");
    printHex(key192,24);

    std::printf("\nCIPHER (ENCRYPT):\n");


    word w192[Nb*(12+1)];
    keyExpansion(key192,w192,6,12);

    byte ct192[16];
    cipher(pt,ct192,w192,12);


    std::printf("INVERSE CIPHER (DECRYPT):\n");

    byte dec192[16];
    invCipher(ct192,dec192,w192,12);



    // AES-256

    std::printf("C.3 AES-256 (Nk=8, Nr=14)\n");


    const byte key256[32] = {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,
        0x0c,0x0d,0x0e,0x0f,
        0x10,0x11,0x12,0x13,
        0x14,0x15,0x16,0x17,
        0x18,0x19,0x1a,0x1b,
        0x1c,0x1d,0x1e,0x1f
    };


    std::printf("PLAINTEXT: ");
    printHex(pt,16);

    // AES_output.txt expects KEY on its own line
    std::printf("\nKEY:\n");
    printHex(key256,32);

    std::printf("\nCIPHER (ENCRYPT):\n");


    word w256[Nb*(14+1)];
    keyExpansion(key256,w256,8,14);

    byte ct256[16];
    cipher(pt,ct256,w256,14);


    std::printf("INVERSE CIPHER (DECRYPT):\n");

    byte dec256[16];
    invCipher(ct256,dec256,w256,14);


    return 0;
}
