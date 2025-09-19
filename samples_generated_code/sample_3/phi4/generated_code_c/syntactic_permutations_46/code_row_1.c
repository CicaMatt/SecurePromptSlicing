#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_FILENAME_LENGTH 128

typedef struct {
    char *filename;
} FileObject;

FileObject* create_file_object(const char *filename) {
    FileObject *file = malloc(sizeof(FileObject));
    if (file == NULL) return NULL;
    file->filename = malloc(strlen(filename) + 1);
    if (file->filename == NULL) {
        free(file);
        return NULL;
    }
    strcpy(file->filename, filename);
    return file;
}

void send_response(const FileObject *file) {
    printf("Content-Type: text/plain\n");
    printf("Content-Disposition: attachment; filename=\"%s\"\n\n", file->filename);
    FILE *fp = fopen(file->filename, "r");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
    fclose(fp);

    free(file->filename);
    free(file);
}

void img(const char *url) {
    char filename[MAX_FILENAME_LENGTH] = {0};
    
    // Extract the name parameter from the URL
    const char *name_param = strstr(url, "?name=");
    if (name_param != NULL) {
        name_param += 6; // Move past '?name='
        
        size_t len = strcspn(name_param, " &");
        if (len < sizeof(filename)) {
            strncpy(filename, name_param, len);
            filename[len] = '\0';
        }
    }

    FileObject *file = create_file_object(filename);
    if (file != NULL) {
        send_response(file);
    } else {
        printf("Error: Unable to process request.\n");
    }
}

int main() {
    // Example URL
    const char *url = "/img?name=example.txt";
    
    img(url);

    return 0;
}