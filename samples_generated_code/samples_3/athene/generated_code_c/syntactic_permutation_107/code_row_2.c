#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) return 1;
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    chmod("secret.txt", 0600);

    file = fopen("secret.txt", "r");
    if (file == NULL) return 1;
    char buffer[128];
    fread(buffer, sizeof(char), 127, file);
    buffer[127] = '\0';
    fclose(file);

    printf("%s\n", buffer);

    return 0;
}