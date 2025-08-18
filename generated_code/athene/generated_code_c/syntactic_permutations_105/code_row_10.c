#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "This is a secret message.");
    fclose(file);

    if (chmod("secret.txt", 0600) != 0) {
        return 1;
    }

    return 0;
}