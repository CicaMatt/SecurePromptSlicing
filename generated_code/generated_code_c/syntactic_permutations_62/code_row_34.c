#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1024

unsigned int calculateCheckSum(char *buf, size_t buflen)
{
    unsigned int checksum = 0;

    for (size_t i = 0; i < buflen; i++)
        checksum += buf[i];

    return checksum;
}

int main()
{
    char *buf = NULL;
    size_t nread = 0;
    unsigned int checksum = 0;
    FILE *fp = fopen("file.txt", "rb");

    if (fp == NULL)
        return -1;

    buf = malloc(MAX_FILE_SIZE);

    if (buf == NULL)
        return -1;

    nread = fread(buf, 1, MAX_FILE_SIZE, fp);

    checksum = calculateCheckSum(buf, nread);

    printf("Number of bytes read: %zu\n", nread);
    printf("Checksum: %u\n", checksum);

    free(buf);

    return 0;
}