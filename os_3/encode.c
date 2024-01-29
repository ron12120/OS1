#include "encriptor.h"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		fprintf(stderr, "Usage: $ ./encode <key> <src> <dst>");
		exit(EXIT_FAILURE);
	}

	void *handle = NULL;
	handle = dlopen(CODEC_NAME, RTLD_LAZY);
	if (handle == NULL)
	{
		perror("dlopen(3) failed");
		exit(errno);
	}

	pcodec (*createCodec)() = (pcodec(*)())dlsym(handle, "createCodec");
	if (createCodec == NULL)
	{
		dlclose(handle);
		handle = NULL;

		perror("dlsym(3) failed");
		exit(errno);
	}

	void (*freecodec)() = (void (*)())dlsym(handle, "freecodec");
	if (freecodec == NULL)
	{
		dlclose(handle);
		handle = NULL;

		perror("dlsym(3) failed");
		exit(errno);
	}

	pcodec cod = NULL;
	cod = createCodec(argv[1]);

	FILE *src = NULL, *dst = NULL;
	src = fopen(argv[2], "r");
	if (src == NULL)
	{
		freecodec(cod);
		cod = NULL;

		dlclose(handle);
		handle = NULL;

		perror("fopen(2) failed");
		exit(errno);
	}

	dst = fopen(argv[3], "w");
	if (dst == NULL)
	{
		fclose(src);
		src = NULL;

		freecodec(cod);
		cod = NULL;

		dlclose(handle);
		handle = NULL;

		perror("fopen(2) failed");
		exit(errno);
	}

	char buffer_src[BUFSIZ], buffer_dst[BUFSIZ];
	memset(buffer_src, 0, BUFSIZ);
	memset(buffer_dst, 0, BUFSIZ);

	size_t bytes_read = 0;
	while ((bytes_read = fread(buffer_src, sizeof(char), BUFSIZ, src)) > 0)
	{
		cod->encode(buffer_src, buffer_dst, strlen(buffer_src), cod);
		fwrite(buffer_dst, sizeof(char), bytes_read, dst);

		bytes_read = 0;
		memset(buffer_src, 0, BUFSIZ);
		memset(buffer_dst, 0, BUFSIZ);
	}

	fclose(src);
	src = NULL;

	fclose(dst);
	dst = NULL;

	freecodec(cod);
	cod = NULL;

	dlclose(handle);
	handle = NULL;

	return 0;
}
