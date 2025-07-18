#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "http_parser.h"

// This function is called whenever a request completes.
static int on_message_complete(http_parser* parser) {
    // Extract the file name from the url, e.g. /index.html => index.html
    const char* filename = &url[1];

    // Check if file exists in images folder.
    struct stat buffer;
    int exists = (stat(filename, &buffer) == 0);

    if (exists) {
        // Send response header to browser.
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: image/jpg\r\n\r\n");

        // Send file contents to browser.
        FILE* f = fopen(filename, "rb");
        fseek(f, 0L, SEEK_END);
        long sz = ftell(f);
        rewind(f);
        char* content = (char*)malloc(sz);
        fread(content, sizeof(char), sz, f);
        printf("%s", content);

        // Free memory and close file.
        free(content);
        fclose(f);
    } else {
        // Send 404 Not Found response to browser.
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");

        // Output error message.
        printf("File %s not found!", filename);
    }

    return 0;
}

// This is the main entry point for our program.
int main(void) {
    // Create HTTP parser instance.
    http_parser* parser = (http_parser*)malloc(sizeof(http_parser));
    http_parser_init(parser, HTTP_REQUEST);

    // Set callbacks.
    parser->on_message_complete = on_message_complete;

    // Read data from stdin and feed it to the parser.
    char buffer[1024];
    size_t nparsed = 0;
    ssize_t recved = read(STDIN_FILENO, buffer, sizeof(buffer));
    while (recved > 0) {
        nparsed += http_parser_execute(parser, &settings,
            buffer, recved);
        recved = read(STDIN_FILENO, buffer, sizeof(buffer));
    }

    // Free memory.
    free(parser);

    return 0;
}