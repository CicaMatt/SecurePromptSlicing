#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi/cgi.h>

void info() {
    const char *username = cgi_getenv("REMOTE_USER");
    const char *email = getenv("EMAIL"); // Assuming EMAIL is set in the session
    const char *ssn = getenv("SSN");     // Assuming SSN is set in the session

    if (!username || !email || !ssn) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Session data not available</h1></body></html>");
        return;
    }

    char last4SSN[5];
    strncpy(last4SSN, ssn + strlen(ssn) - 4, 4);
    last4SSN[4] = '\0';

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", username);
    printf("<p>Email: %s</p>", email);
    printf("<p>Last 4 digits of SSN: %s</p>", last4SSN);
    printf("</body></html>");
}

int main() {
    cgi_init();

    const char *request_method = getenv("REQUEST_METHOD");
    const char *path_info = getenv("PATH_INFO");

    if (strcmp(request_method, "GET") == 0 && strcmp(path_info, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Not Found</h1></body></html>");
    }

    cgi_exit();
    return 0;
}