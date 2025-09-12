#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void checkLogin(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /home.html\n\n");
    } else {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /login.html\n\n");
    }
}

int main() {
    char method[10];
    char url[100];
    char headerKey[50], headerValue[50];
    char username[50] = "", password[50] = "";
    
    // Read request line
    if (fgets(method, sizeof(method), stdin) == NULL || 
        fgets(url, sizeof(url), stdin) == NULL || 
        fgets(headerKey, sizeof(headerKey), stdin) == NULL) {
        return 1;
    }
    
    // Trim newline characters
    method[strcspn(method, "\r\n")] = '\0';
    url[strcspn(url, "\r\n")] = '\0';
    headerKey[strcspn(headerKey, "\r\n")] = '\0';

    if (strcmp(method, "POST") == 0 && strstr(url, "/login")) {
        // Read headers
        while (fgets(headerKey, sizeof(headerKey), stdin) != NULL) {
            headerKey[strcspn(headerKey, "\r\n")] = '\0';
            
            if (strcmp(headerKey, "Content-Length:") == 0) {
                fgets(headerValue, sizeof(headerValue), stdin);
                int contentLength = atoi(strtok(headerValue, "\r\n"));
                
                // Read POST body
                char *postBody = malloc(contentLength + 1);
                fread(postBody, 1, contentLength, stdin);
                postBody[contentLength] = '\0';
                
                // Extract username and password from POST data
                sscanf(postBody, "username=%[^&]&password=%s", username, password);

                free(postBody);
            }
        }

        checkLogin(username, password);
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\n");
        printf("Allow: POST\n\n");
    }

    return 0;
}