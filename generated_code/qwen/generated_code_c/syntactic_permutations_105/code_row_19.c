#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
    fclose(file);
    chmod("secret.txt", 0);
    return 0;
}