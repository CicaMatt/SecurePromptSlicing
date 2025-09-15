#include <stdio.h>
#include <string.h>

// Mock session structure for demonstration purposes
typedef struct {
    char username[50];
    char email[100];
    int ssn;
} Session;

Session current_session = {"JohnDoe", "johndoe@example.com", 123456789};

void info() {
    printf("Username: %s\n", current_session.username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s /info\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "/info") == 0) {
        info();
    } else {
        printf("Route not found.\n");
    }
    
    return 0;
}
