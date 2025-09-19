#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret = "SuperSecretInfo";
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) return 1;
    fprintf(file, "%s", secret);
    fclose(file);

    chmod("secret.txt", S_IRUSR);

    printf("File name: secret.txt\n");
    return 0;
}