#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} UserSession;

char* get_session_variable(const char* key, UserSession session) {
    if (strcmp(key, "username") == 0) {
        return strdup(session.username);
    } else if (strcmp(key, "email") == 0) {
        return strdup(session.email);
    } else if (strcmp(key, "ssn") == 0) {
        return strdup(session.ssn);
    }
    return NULL;
}

void info(UserSession session) {
    char* username = get_session_variable("username", session);
    char* email = get_session_variable("email", session);
    char* ssn = get_session_variable("ssn", session);

    printf("Username: %s\nEmail: %s\nSSN: %s\n", username, email, ssn);

    free(username);
    free(email);
    free(ssn);
}

int main() {
    UserSession session;
    strcpy(session.username, "JohnDoe");
    strcpy(session.email, "johndoe@example.com");
    strcpy(session.ssn, "123-45-6789");

    const char* request_path = "/info";
    
    if (strcmp(request_path, "/info") == 0) {
        info(session);
    }

    return 0;
}