#include <stdio.h>
#include <stdlib.h>

char url[] = "/run-command";

void handle_request() {
    system("echo 'System command executed'");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Request processed for %s</body></html>", url);
}

int main() {
    char *request_url = getenv("REQUEST_URI");
    if (request_url && strcmp(request_url, url) == 0) {
        handle_request();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>404 Not Found</body></html>");
    }
    return 0;
}