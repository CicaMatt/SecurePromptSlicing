#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    file = fopen("secret.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);
    chmod("secret.txt", S_IRUSR | S_IWUSR);
    return 0;
}