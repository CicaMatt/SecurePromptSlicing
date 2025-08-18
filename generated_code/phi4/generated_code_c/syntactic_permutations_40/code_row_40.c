#include <stdio.h>
#include <string.h>

#define SESSION_USERNAME "john_doe"
#define SESSION_EMAIL "john@example.com"
#define SESSION_SSN "123-45-6789"

void info() {
    char ssn[11];
    strncpy(ssn, SESSION_SSN + 6, 4);
    ssn[4] = '\0';

    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html>\n");
    printf("<head><title>Info Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", SESSION_USERNAME);
    printf("<p>Email: %s</p>\n", SESSION_EMAIL);
    printf("<p>Last 4 digits of SSN: %s</p>\n", ssn);
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    const char *request_method = "GET";
    const char *path_info = "/info";

    if (strcmp(request_method, "GET") == 0 && strcmp(path_info, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("404 Not Found\n");
    }

    return 0;
}