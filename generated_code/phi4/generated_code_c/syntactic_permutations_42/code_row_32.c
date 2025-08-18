#include <stdio.h>
#include <string.h>

#define MAX_SESSION_SIZE 256

typedef struct {
    char key[MAX_SESSION_SIZE];
    char value[MAX_SESSION_SIZE];
} Session;

Session session[3];

void init_session() {
    strcpy(session[0].key, "username");
    strcpy(session[0].value, "user@example.com");

    strcpy(session[1].key, "email");
    strcpy(session[1].value, "user@example.com");

    strcpy(session[2].key, "ssn");
    strcpy(session[2].value, "123-45-6789");
}

const char* get_session_value(const char *key) {
    for (int i = 0; i < 3; ++i) {
        if (strcmp(session[i].key, key) == 0) {
            return session[i].value;
        }
    }
    return "";
}

void handle_request() {
    const char* email = get_session_value("email");
    const char* ssn = get_session_value("ssn");

    printf("Content-Type: text/plain\n\n");
    printf("Email: %s, SSN: %s\n", email, ssn);
}

int main(int argc, char *argv[]) {
    init_session();

    if (argc < 2) {
        fprintf(stderr, "Usage: %s /info\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "/info") == 0) {
        handle_request();
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}