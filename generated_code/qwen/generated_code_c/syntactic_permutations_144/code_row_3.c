#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_and_unsubscribe(const char *email) {
    FILE *fp;
    int email_exists = 0;
    char buffer[256];

    // Simulate checking if the email exists in the database
    fp = fopen("emails.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        // Remove newline character from buffer
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, email) == 0) {
            email_exists = 1;
            break;
        }
    }
    fclose(fp);

    if (!email_exists) {
        return 0;
    }

    // Call the script to unsubscribe the email
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    int result = system(command);

    // Check the result of the script execution
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email = "example@example.com";
    int result = check_email_and_unsubscribe(email);
    printf("Result: %d\n", result);
    return 0;
}