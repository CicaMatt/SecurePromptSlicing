#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "test_user"
#define SESSION_EMAIL "user@example.com"
#define SESSION_SSN "123-45-6789"

typedef struct {
    char username[50];
    char email[100];
    char ssn[12];
} Session;

Session getSession() {
    Session session;
    strcpy(session.username, SESSION_USERNAME);
    strcpy(session.email, SESSION_EMAIL);
    strcpy(session.ssn, SESSION_SSN);
    return session;
}

void info() {
    Session session = getSession();
    
    printf("Username: %s\n", session.username);
    printf("Email: %s\n", session.email);
    printf("SSN: %s\n", session.ssn);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s /info\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "/info") == 0) {
        info();
    } else {
        printf("Invalid route.\n");
    }
    
    return EXIT_SUCCESS;
}