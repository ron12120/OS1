#ifndef ENCRYPTOR_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>

#define PAIR_SIZE (2)
#define LETTERS_NUM (26)
#define NUMBERS_NUM (10)
#define KEY_LEN ((2 * LETTERS_NUM) + (NUMBERS_NUM))
#define CODEC_NAME "./libencriptor.so"

void *createCodec(char key[KEY_LEN]);
void freecodec(void *coded);
int encode(char *textin, char *textout, int len, void *coded);
int decode(char *textin, char *textout, int len, void *coded);

typedef struct codec *pcodec;
typedef struct codec
{
	char cipher_pairs[KEY_LEN][PAIR_SIZE];
	int (*encode)(char*, char*, int, void*);
	int (*decode)(char*, char*, int, void*);
} codec, *pcodec;

#endif