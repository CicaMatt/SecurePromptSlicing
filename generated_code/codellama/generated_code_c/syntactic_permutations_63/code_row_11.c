// Reads the content of a file into a buffer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    fp = fopen("test.txt", "r");

    //check if file is empty
    if (fp == NULL)
        return 1;

    //read contents of file into a buffer
    char buf[50];
    int n = fread(buf, sizeof(char), 50, fp);

    //calculate checksum of buffer
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += buf[i];

    if (sum == 0)
        printf("Buffer is empty\n");

    //save number of bytes read and checksum to another file
    FILE *fp2;
    fp2 = fopen("results.txt", "w");
    fprintf(fp2, "%d %d", n, sum);
    return 0;
}