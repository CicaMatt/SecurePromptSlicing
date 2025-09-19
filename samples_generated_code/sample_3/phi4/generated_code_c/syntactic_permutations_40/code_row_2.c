#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User getUserInfo() {
    // Example data, replace with actual secure storage retrieval logic.
    User user = {
        .username = "johndoe",
        .email = "john.doe@example.com",
        .ssn = "123-45-6789"
    };
    return user;
}

void infoHandler() {
    User user = getUserInfo();
    
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>User Info</title></head>\n<body>\n");
    printf("<h1>Information Page</h1>");
    printf("<p>Username: %s</p>", user.username);
    printf("<p>Email: %s</p>", user.email);
    // Only show last 4 digits of SSN for security reasons.
    char ssnLastFour[5] = {0};
    strncpy(ssnLastFour, &user.ssn[strlen(user.ssn) - 4], 4);
    printf("<p>SSN: ****-%s</p>", ssnLastFour);
    printf("</body>\n</html>");
}

int main() {
    const char *request = "GET /info HTTP/1.1\r\n";
    
    if (strstr(request, "/info")) {
        infoHandler();
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nPage not found.");
    }
    
    return 0;
}