#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


#define GPG "gpg"
#define OUT_FLAG "--output"
#define GZIP_RES "res.tar.gz"
#define DECRYPTION_FLAG "--decrypt"
#define ENCRYPTION_ALGO_FLAG "--cipher-algo"
#define ENCRYPTION_ALGO "AES256"
#define GPG_RESULT "res.tar.gz.gpg"
#define GPG_LEN 8

#define UNGZIP_LEN 3
#define UNGZIP "gunzip"
#define UNGZIP_RESULT "res.tar.gz"

#define TAR "tar"
#define TAR_UNCOMPRESS "-xf"
#define TAR_INPUT "res.tar"
#define TAR_LEN 4

#define CLEANUP_LEN 3
#define RM "rm"


char *gpg_arr[GPG_LEN] =
{
    GPG,
    OUT_FLAG,
    GZIP_RES,
    DECRYPTION_FLAG,
    ENCRYPTION_ALGO_FLAG,
    ENCRYPTION_ALGO,
    GPG_RESULT,
    NULL
};

char *gzip_arr[UNGZIP_LEN] = 
{
    UNGZIP,
    UNGZIP_RESULT,
    NULL
};

char *tar_arr[TAR_LEN] = 
{
    TAR,
    TAR_UNCOMPRESS,
    TAR_INPUT,
    NULL
};
char *cleanup[CLEANUP_LEN] =
    {
        RM,
        TAR_INPUT,
        NULL
    };



int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: $ ./myunzip <File> ");
        exit(errno);
    }

    int pid = 0;

    pid = fork();
    if (pid == 0)
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
        execvp(gzip_arr[0], gzip_arr);
    }
    else
    {
        wait(NULL);
    }

    pid =0;
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
        execvp(cleanup[0], cleanup);
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
