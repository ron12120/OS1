#include "encriptor.h"

bool isKeyValid(const char *key)
{
	int length = strlen(key);
	// Length check
	if (length != 62)
	{
		return false;
	}

	int lowercaseCount = 0, uppercaseCount = 0, digitCount = 0;
	bool charSeen[128] = {false}; // Assuming ASCII character set

	for (int i = 0; i < length; ++i)
	{
		unsigned char ch = key[i];

		// Check if character is already seen
		if (charSeen[ch])
		{
			return false; // Duplicate character found
		}
		charSeen[ch] = true;

		if (islower(ch))
		{
			lowercaseCount++;
		}
		else if (isupper(ch))
		{
			uppercaseCount++;
		}
		else if (isdigit(ch))
		{
			digitCount++;
		}
	}

	// Check for correct count of each type
	return lowercaseCount == 26 && uppercaseCount == 26 && digitCount == 10;
}

char encript(char decryption, pcodec this)
{
	int i = 0;
	for (; i < KEY_LEN; i++)
	{
		if (this->cipher_pairs[i][0] == decryption)
		{
			return (this->cipher_pairs[i][1]);
		}
	}
	return '\0';
}

int encode(char *textin, char *textout, int len, void *coded)
{
	if (coded == NULL)
	{
		return 1;
	}

	char ciphertext[len];
	memset(ciphertext, 0, len);

	pcodec cod = (pcodec)coded;

	int i = 0;
	for (; i < len; i++)
	{
		ciphertext[i] = encript(textin[i], cod);
	}
	ciphertext[i] = '\0';
	strncpy(textout, (const char *)ciphertext, len + 1);

	return 0;
}

char decript(char ciphertext, pcodec this)
{
	int i = 0;
	for (; i < KEY_LEN; i++)
	{
		if (this->cipher_pairs[i][1] == ciphertext)
		{
			return (this->cipher_pairs[i][0]);
		}
	}
	return '\0';
}

int decode(char *textin, char *textout, int len, void *coded)
{
	if (coded == NULL)
	{
		return 1;
	}

	char ciphertext[len];
	memset(ciphertext, 0, len);

	pcodec cod = (pcodec)coded;

	int i = 0;
	for (; i < len; i++)
	{
		ciphertext[i] = decript(textin[i], cod);
	}
	ciphertext[i] = '\0';
	strncpy(textout, (const char *)ciphertext, len + 1);

	return 0;
}

void *createCodec(char key[KEY_LEN])
{
	pcodec cod = NULL;
	cod = (pcodec)calloc(1, sizeof(codec));
	if (cod == NULL)
	{
		perror("calloc(3) failed");
		exit(errno);
	}

	if (!isKeyValid(key))
	{
		printf("You entered a bad key");
		return NULL;
	}

	int i = 0;
	for (i = 0; i < LETTERS_NUM; i++)
	{
		cod->cipher_pairs[i][0] = (char)(i + 97);
		cod->cipher_pairs[i][1] = key[i];
	}
	for (i = 0; i < LETTERS_NUM; i++)
	{
		cod->cipher_pairs[i + LETTERS_NUM][0] = (char)(i + 65);
		cod->cipher_pairs[i + LETTERS_NUM][1] = key[i];
	}
	for (i = 0; i < NUMBERS_NUM; i++)
	{
		cod->cipher_pairs[i + (2 * LETTERS_NUM)][0] = (i != (NUMBERS_NUM - 1)) ? (char)(i + 1) : (char)(0);
		cod->cipher_pairs[i + (2 * LETTERS_NUM)][1] = key[i];
	}

	cod->encode = encode;

	cod->decode = decode;

	return cod;
}

void freecodec(void *codec)
{
	free(codec);
	codec = NULL;
}
