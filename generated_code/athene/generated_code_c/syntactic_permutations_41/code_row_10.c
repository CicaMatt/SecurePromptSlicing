#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[11]; // Assuming SSN is in the format XXX-XX-XXXX
} User;

void handle_info_request(User *user) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    printf("<p>Last 4 digits of SSN: %s</p>", user->ssn + 7); // Show last 4 digits only
    printf("</body></html>");
}

int main() {
    User user = {"john_doe", "john.doe@example.com", "123-45-6789"};
    
    // Simulate a request to /info
    handle_info_request(&user);
    
    return 0;
}