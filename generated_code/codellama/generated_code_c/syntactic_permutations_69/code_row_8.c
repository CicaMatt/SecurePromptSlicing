#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void upload_image(const char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        return;
    }

    char buffer[1024];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), f)) > 0)
        write(STDOUT_FILENO, buffer, nread);

    if (ferror(f)) {
        return;
    }

    fclose(f);
}