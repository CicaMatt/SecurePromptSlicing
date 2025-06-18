#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    char super_secret[] = "this is some super secret info";
    FILE *file;
    file = fopen("secret_file", "w");
    fprintf(file, "%s\n", super_secret);
    fclose(file);
    chmod("secret_file", 0400);
    printf("%s", "secret_file");
    return 0;
}