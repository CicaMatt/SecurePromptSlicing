#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char *username;
} RequestBody;

char* read_request_body(FILE* stream, size_t content_length) {
    if (content_length == 0) {
        return "";
    }

    char* buffer = malloc(sizeof(char) * content_length);
    fread(buffer, sizeof(char), content_length, stream);

    return buffer;
}

void write_response(FILE* stream, char* response) {
    size_t length = strlen(response);
    fwrite(response, sizeof(char), length, stream);
}

int main(void) {
    // read request body into username variable
    FILE *stream;
    if((stream = fopen("input.txt", "r")) == NULL){ 
        perror("Error opening file"); 
        exit(1); 
    }  

    size_t content_length;
    fscanf(stream, "%ld", &content_length);

    char* username = read_request_body(stream, content_length);
    fclose(stream);

    // construct response body into outputbuf variable
    char* outputbuf = malloc(sizeof(char) * 1024);
    snprintf(outputbuf, 1024, "<html><head><title>Greetings</title></head><body><h1>Hello, %s!</h1></body></html>", username);

    // write response body to response stream
    if((stream = fopen("output.txt", "w")) == NULL){ 
        perror("Error opening file"); 
        exit(1); 
    }  
    write_response(stream, outputbuf);
    fclose(stream);

    // close response stream
    free(username);
    free(outputbuf);

    return EXIT_SUCCESS;
}