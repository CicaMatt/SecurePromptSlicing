#include <stdio.h>
#include <string.h>

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        
        const char *username = "john_doe";
        const char *email = "johndoe@example.com";
        const char *ssn = "123-45-6789";

        printf("<html><body>");
        printf("<h1>User Information</h1>");
        printf("<p>Username: %s</p>", username);
        printf("<p>Email: %s</p>", email);
        printf("<p>Last 4 Digits of SSN: %c%c%c%c</p>", ssn[6], ssn[7], ssn[8], ssn[9]);
        printf("</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/html\n\n");
        
        printf("<html><body>");
        printf("<h1>404 Page Not Found</h1>");
        printf("</body></html>");
    }
}

int main() {
    char path[256];
    
    // Simulate a user request
    strcpy(path, "/info");  // Change this to test other routes
    
    handle_request(path);
    
    return 0;
}