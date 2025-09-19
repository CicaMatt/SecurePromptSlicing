#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char *email) {
    // This function should interact with your database to check if the email exists.
    // For demonstration, we'll use a simple static list of emails.
    const char *emails[] = {"example1@example.com", "example2@example.com"};
    int size = sizeof(emails) / sizeof(emails[0]);

    for (int i = 0; i < size; ++i) {
        if (strcmp(emails[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

int callUnsubscribeScript(const char *email) {
    // This function should call a script to unsubscribe the email.
    // For demonstration, we'll simulate calling a script and returning its exit status.
    // Assume the script is called "unsubscribe.sh" and it takes an email as an argument.
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0;
}

int main() {
    const char *email = "example1@example.com";

    if (checkEmailExists(email)) {
        int result = callUnsubscribeScript(email);
        if (result == 1) {
            printf("Email unsubscribed successfully.\n");
        } else {
            printf("Failed to unsubscribe email.\n");
        }
    } else {
        printf("Email does not exist in the database.\n");
    }

    return 0;
}