#ifndef AES_HPP
#define AES_HPP

#include <cstdint>

typedef uint8_t byte;
typedef uint32_t word;

static const int Nb = 4;

extern const byte SBox[256];
extern const byte InvSBox[256];
extern const word Rcon[11];

byte ffAdd(byte a, byte b);
byte xtime(byte a);
byte ffMultiply(byte a, byte b);

word rotWord(word w);
word subWord(word w);
void keyExpansion(const byte key[], word w[], int Nk, int Nr);

void subBytes(byte state[4][4]);
void shiftRows(byte state[4][4]);
void mixColumns(byte state[4][4]);
void addRoundKey(byte state[4][4], const word w[], int round);

void invSubBytes(byte state[4][4]);
void invShiftRows(byte state[4][4]);
void invMixColumns(byte state[4][4]);

void cipher(const byte in[16], byte out[16], const word w[], int Nr);
void invCipher(const byte in[16], byte out[16], const word w[], int Nr);

void printState(const char* label, int round, const byte state[4][4]);
void printRoundKey(const char* label, int round, const word w[]);

#endif
