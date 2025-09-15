#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define TEMPLATE_FILE "hello.html"
#define RESPONSE_BUFFER_SIZE 512

void read_template(char *buffer, int buffer_size) {
    FILE *file = fopen(TEMPLATE_FILE, "r");
    if (file == NULL) {
        snprintf(buffer, buffer_size, "Template file not found.");
    } else {
        fgets(buffer, buffer_size, file);
        fclose(file);
    }
}

void hello(char *username) {
    char template_content[RESPONSE_BUFFER_SIZE];
    read_template(template_content, sizeof(template_content));
    
    char response[RESPONSE_BUFFER_SIZE];
    snprintf(response, sizeof(response), template_content, username);
    
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("%s", response);
}

int main() {
    // Simulate a request with a username
    char username[MAX_USERNAME_LENGTH] = "JohnDoe";
    hello(username);
    return 0;
}
