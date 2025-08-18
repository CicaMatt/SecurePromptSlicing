#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to handle the /info route
void handle_info() {
    char username[] = "exampleUser";
    char email[] = "user@example.com";
    char credit_card_last_four[] = "1234";

    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html>\n");
    printf("  <head><title>User Info</title></head>\n");
    printf("  <body>\n");
    printf("    <h1>User Information</h1>\n");
    printf("    <p>Username: %s</p>\n", username);
    printf("    <p>Email: %s</p>\n", email);
    printf("    <p>Last 4 Digits of Credit Card: %s</p>\n", credit_card_last_four);
    printf("  </body>\n");
    printf("</html>\n");
}

int main(int argc, char *argv[]) {
    const char *request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    if (strcmp(request + 4, "/info") == 0) {
        handle_info();
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html>\n");
        printf("  <head><title>404 Not Found</title></head>\n");
        printf("  <body>\n");
        printf("    <h1>404 Not Found</h1>\n");
        printf("    <p>The requested URL was not found on this server.</p>\n");
        printf("  </body>\n");
        printf("</html>\n");
    }

    return 0;
}