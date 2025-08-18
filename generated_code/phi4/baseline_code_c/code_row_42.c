#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a session storage with a simple struct
typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

Session current_session = {
    .username = "JohnDoe",
    .email = "john.doe@example.com",
    .ssn = "123-45-6789"
};

void info() {
    printf("Username: %s\n", current_session.username);
    printf("Email: %s\n", current_session.email);
    printf("SSN: %s\n", current_session.ssn);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s /info\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "/info") == 0) {
        info();
    } else {
        printf("Route not found.\n");
    }

    return EXIT_SUCCESS;
}