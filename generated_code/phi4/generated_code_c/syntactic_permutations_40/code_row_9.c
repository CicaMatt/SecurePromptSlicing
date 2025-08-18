#include <stdio.h>
#include <string.h>

#define MAX_SESSION_SIZE 256

typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5]; // SSN last four digits
} Session;

Session session = {"user123", "user@example.com", "6789"};

void info() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html>\n");
    printf("<head><title>Info Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", session.username);
    printf("<p>Email: %s</p>\n", session.email);
    printf("<p>Last 4 digits of SSN: %s</p>\n", session.ssn_last4);
    printf("</body>\n");
    printf("</html>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    const char* request = argv[1];
    
    if (strcmp(request, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html>\n<head><title>Not Found</title></head>\n<body>\n<h1>404 Not Found</h1>\n</body>\n</html>");
    }

    return 0;
}