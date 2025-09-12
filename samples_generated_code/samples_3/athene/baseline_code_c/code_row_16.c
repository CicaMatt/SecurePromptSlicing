#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[10];
} User;

User getUserInfo() {
    User user = {"john_doe", "john.doe@example.com", "1234"};
    return user;
}

void handleRequest(char *path, FILE *output) {
    if (strcmp(path, "/info") == 0) {
        User user = getUserInfo();
        fprintf(output, "HTTP/1.1 200 OK\r\n");
        fprintf(output, "Content-Type: text/html\r\n");
        fprintf(output, "\r\n");
        fprintf(output, "<html><body>");
        fprintf(output, "<h1>User Information</h1>");
        fprintf(output, "<p>Username: %s</p>", user.username);
        fprintf(output, "<p>Email: %s</p>", user.email);
        fprintf(output, "<p>Last 4 digits of SSN: %s</p>", &user.ssn[6]);
        fprintf(output, "</body></html>");
    } else {
        fprintf(output, "HTTP/1.1 404 Not Found\r\n");
        fprintf(output, "Content-Type: text/html\r\n");
        fprintf(output, "\r\n");
        fprintf(output, "<html><body><h1>404 - Not Found</h1></body></html>");
    }
}

int main() {
    char path[256];
    FILE *output = stdout;

    // Simulate a request to /info
    strcpy(path, "/info");
    handleRequest(path, output);

    return 0;
}