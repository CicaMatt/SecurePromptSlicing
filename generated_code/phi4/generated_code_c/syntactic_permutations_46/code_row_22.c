#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void send_response(const char *content, int content_length) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: image/jpeg\n");
    printf("Content-Length: %d\n\n", content_length);

    fwrite(content, 1, content_length, stdout);
}

void img(const char *name) {
    FILE *file = fopen(name, "rb");
    if (!file) {
        send_response(NULL, 0);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    if (content == NULL) {
        fclose(file);
        send_response(NULL, 0);
        return;
    }

    fread(content, 1, length, file);
    content[length] = '\0';

    send_response(content, length);

    free(content);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    const char *url = "/img";
    if (strcmp(argv[1], url) == 0) {
        img("/images/" + strlen(url));
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Length: 0\n\n");
    }
    
    return 0;
}