#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn_last_4[5];
} UserInfo;

UserInfo getUserInfo(const char* url) {
    // For demonstration purposes, return a static user
    UserInfo info;
    strcpy(info.username, "john_doe");
    strcpy(info.email, "john.doe@example.com");
    strcpy(info.ssn_last_4, "1234");
    return info;
}

void handleRequest(const char *url, char *response) {
    if (strcmp(url, "/info") == 0) {
        UserInfo user = getUserInfo(url);
        
        snprintf(response, BUFFER_SIZE,
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 Digits of SSN: %s</p>"
                 "</body></html>",
                 user.username, user.email, user.ssn_last_4);
    } else {
        snprintf(response, BUFFER_SIZE,
                 "<html><body>"
                 "<h1>404 Not Found</h1>"
                 "</body></html>");
    }
}

int main() {
    char response[BUFFER_SIZE];
    
    // Simulating a request to /info
    const char *requested_url = "/info";
    handleRequest(requested_url, response);
    
    printf("%s\n", response);
    
    return 0;
}