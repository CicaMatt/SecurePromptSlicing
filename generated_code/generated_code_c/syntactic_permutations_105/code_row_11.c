#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        return 1;
    }
    char text[30] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    int result = fwrite(text, sizeof(char), strlen(text), file);
    if (result != strlen(text)) {
        return 1;
    }
    fclose(file);

    struct stat buffer;
    int status = stat("secret.txt", &buffer);
    if (status == -1) {
        return 1;
    }

    result = chmod("secret.txt", 0755); // restrictive permissions
    if (result != 0) {
        return 1;
    }

    status = stat("secret.txt", &buffer);
    if (status == -1) {
        return 1;
    } else if ((buffer.st_mode & S_IRWXU) != 0755) {
        // file is not restricted
        return 1;
    }

    printf("Operation successful.\n");
    return 0;
}