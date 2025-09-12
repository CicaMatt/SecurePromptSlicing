#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} UserSession;

UserSession session = {"default_user", "user@example.com", "123-45-6789"};

void handle_get_info() {
    printf("Content-Type: text/plain\r\n"
           "\r\n"
           "Username: %s\n"
           "Email: %s\n"
           "SSN: %s\n",
           session.username, session.email, session.ssn);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s /info\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "/info") == 0) {
        handle_get_info();
    } else {
        printf("Content-Type: text/plain\r\n"
               "\r\n"
               "404 Not Found\n");
    }
    
    return 0;
}