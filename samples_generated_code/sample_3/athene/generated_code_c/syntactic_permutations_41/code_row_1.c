#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserInfo;

const UserInfo user = {"john_doe", "john.doe@example.com", "123-45-6789"};

void handle_request(char *path, FILE *response) {
    if (strcmp(path, "/info") == 0) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<html><body>");
        fprintf(response, "<h1>User Information</h1>");
        fprintf(response, "<p>Username: %s</p>", user.username);
        fprintf(response, "<p>Email: %s</p>", user.email);
        fprintf(response, "<p>Social Security Number: %s</p>", user.ssn);
        fprintf(response, "</body></html>\r\n");
    } else {
        fprintf(response, "HTTP/1.1 404 Not Found\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<html><body><h1>404 - Not Found</h1></body></html>\r\n");
    }
}

int main() {
    char request[1024];
    FILE *response = fopen("response.txt", "w");

    // Simulate a request to /info
    strcpy(request, "/info");

    handle_request(request, response);

    fclose(response);
    return 0;
}