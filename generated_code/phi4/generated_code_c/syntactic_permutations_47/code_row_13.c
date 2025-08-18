#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void send_file_to_browser(const char* filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    // Send file to browser (here we just print the content to stdout)
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, file);
    fclose(file);

    string[fsize] = 0;
    printf("%s\n", string);
    free(string);
}

void check_and_send_file(const char* url) {
    const char *folder_path = "./files/"; // Define the folder path
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", folder_path, url);

    struct stat buffer;
    if (stat(filepath, &buffer) == 0) {
        send_file_to_browser(filepath);
    } else {
        printf("File not found\n");
    }
}

int main() {
    const char *url = "example.txt"; // URL to check
    check_and_send_file(url);
    return 0;
}