#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, request);
    
    if (bytesRead == 0 || feof(request)) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }
    
    buffer[bytesRead] = '\0';
    char *usernameStart = strstr(buffer, "GET /?username=");
    if (!usernameStart) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }
    
    usernameStart += strlen("GET /?username=");
    char *usernameEnd = strchr(usernameStart, ' ');
    if (!usernameEnd) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }
    
    size_t usernameLength = usernameEnd - usernameStart;
    char *username = (char *)malloc(usernameLength + 1);
    if (!username) {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }
    
    strncpy(username, usernameStart, usernameLength);
    username[usernameLength] = '\0';
    
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\nConnection: close\r\n\r\nHello %s", strlen(username) + 8, username);
    
    free(username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }
    
    FILE *response = fopen("response.txt", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }
    
    http_hello_page(request, response);
    
    fclose(request);
    fclose(response);
    return 0;
}