#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp, *outfile;
    char buffer[1024];
    int bytes_read;
    unsigned short checksum = 0;
    fp = fopen("sample.txt", "r");
    outfile = fopen("output.txt", "w");

    if (fp == NULL || outfile == NULL)
        exit(EXIT_FAILURE);

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        for (int i = 0; i < bytes_read; i++)
            checksum += buffer[i];
    }

    if (checksum == 0)
    {
        for (int i = 0; i < bytes_read; i++)
            fputc(buffer[i], outfile);
    }

    fprintf(outfile, "bytes read: %d\n", bytes_read);
    fprintf(outfile, "checksum: %u\n", checksum);

    fclose(fp);
    fclose(outfile);

    return 0;
}