#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
    FILE *f = fopen("secret.txt", "w");
    fprintf(f, "super secret info goes here");
    fclose(f);
    chmod("secret.txt", S_IRUSR);
    printf("secret.txt\n");
}