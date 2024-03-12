#include "encriptor.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: $ ./decode <key> <src> <dst>");
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

    int buffer_src;
    char buffer_dst;
    memset(&buffer_src, 0, sizeof(int));
    memset(&buffer_dst, 0, sizeof(char));

    while ((buffer_src = fgetc(src)) != EOF)
    {
        if (buffer_src == '\n' || buffer_src == ' ' || buffer_src == '\t')
        {
            buffer_dst = buffer_src;
        }
        else
        {
            cod->decode((char *)&buffer_src, &buffer_dst, 1, cod);
        }

        fwrite(&buffer_dst, sizeof(char), 1, dst);

        memset(&buffer_src, 0, sizeof(int));
        memset(&buffer_dst, 0, sizeof(char));
    }

    fclose(src);
    fclose(dst);

    freecodec(cod);
    cod = NULL;

    dlclose(handle);
    handle = NULL;

    return 0;
}
