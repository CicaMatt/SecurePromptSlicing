#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return 1;
    }
    fwrite(content, sizeof(char), strlen(content), file);
    fclose(file);

    chmod(filename, 0600);

    return 0;
}