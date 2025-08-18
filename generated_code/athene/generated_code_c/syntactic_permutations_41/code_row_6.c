#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[11]; // Assuming SSN is in the format XXX-XX-XXXX
} User;

User getUserInfo() {
    User user = {"john_doe", "john.doe@example.com", "123-45-6789"};
    return user;
}

void sendUserInfo(User user) {
    char response[200];
    snprintf(response, sizeof(response), 
             "<html><body><h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p></body></html>",
             user.username, user.email, &user.ssn[7]);
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("%s", response);
}

int main() {
    User user = getUserInfo();
    sendUserInfo(user);
    return 0;
}