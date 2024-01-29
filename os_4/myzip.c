#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


#define TAR "tar"
#define TAR_COMPRESS "-cf"
#define TAR_RESULT "res.tar"
#define TAR_LEN 5


#define GZIP_LEN 3
#define GZIP "gzip"
#define GZIP_RESULT "res.tar.gz"

#define GPG "gpg"
#define OUT_FLAG "--output"
#define SYMMETRIC_FLAG "--symmetric"
#define ENCRYPTION_ALGO_FLAG "--cipher-algo"
#define ENCRYPTION_ALGO "AES256"
#define GPG_RESULT "res.tar.gz.gpg"
#define ARMOR_FLAG "--armor"
#define PASSPHRASE_FLAG "--passphrase"
#define PASSPHRASE "password"
#define GPG_LEN 11


#define CLEANUP_LEN 3
#define RM "rm"


char **tar_arr = NULL;

char *gzip_arr[GZIP_LEN] = 
{
    GZIP,
    TAR_RESULT,
    NULL
};

    char *gpg_arr[GPG_LEN] = 
{
    GPG,
    OUT_FLAG,
    GPG_RESULT,
    SYMMETRIC_FLAG,
    ENCRYPTION_ALGO_FLAG,
    ENCRYPTION_ALGO,
    ARMOR_FLAG,
    PASSPHRASE_FLAG,
    PASSPHRASE,
    GZIP_RESULT,
    NULL
};
char *cleanup[CLEANUP_LEN] =
    {
        RM,
        GZIP_RESULT,
        NULL
    };


void tar(char *file_name)
{
    tar_arr = (char**)(calloc(TAR_LEN, sizeof(char*)));
    if(!tar_arr)
    {
        perror("calloc(3) failed");
        exit(errno);
    }
    tar_arr[0] = TAR;
    tar_arr[1] = TAR_COMPRESS;
    tar_arr[2] = TAR_RESULT;
    tar_arr[3] = file_name;
    tar_arr[4] = NULL;
}


int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: $ ./myzip <F1> ...");
        exit(errno);
    }

    int pid = 0;

    tar(argv[1]);

    pid = fork();
    if(pid == 0)
    {
        execvp(tar_arr[0], tar_arr);
    }
    else
    {
        wait(NULL);
    }

    pid = 0;
    pid = fork();
    if(pid == 0)
    {
        execvp(gzip_arr[0], gzip_arr);
    }
    else
    {
        wait(NULL);
    }

    pid = 0;
    pid = fork();
    if(pid == 0)
    {
        execvp(gpg_arr[0], gpg_arr);
    }
    else
    {
        wait(NULL);
    }
    
    pid = 0;
    pid = fork();
    if(pid == 0)
    {
        execvp(cleanup[0], cleanup);
    }
    else
    {
        wait(NULL);
    }

    
    free(tar_arr);

    return 0;
}