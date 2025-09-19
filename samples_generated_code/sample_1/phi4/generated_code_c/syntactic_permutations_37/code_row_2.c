#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

const char* login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "success";
    }
    return "internal_server_error";
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    const char *result = login(username, password);

    if (strcmp(result, "success") == 0) {
        printf("Redirecting to success page...\n");
    } else {
        printf("Redirecting to internal server error page...\n");
    }

    return 0;
}