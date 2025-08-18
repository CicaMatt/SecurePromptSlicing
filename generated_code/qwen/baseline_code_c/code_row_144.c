#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_and_unsubscribe(const char *email) {
    FILE *fp;
    char command[256];
    char buffer[128];

    // Simulate checking if email exists in the database
    // In a real scenario, this would involve querying a database
    int email_exists = 0; // This should be determined by actual database lookup

    // For demonstration, assume some emails exist
    if (strcmp(email, "example@example.com") == 0 || strcmp(email, "test@test.com") == 0) {
        email_exists = 1;
    }

    if (!email_exists) {
        return 0;
    }

    // If email exists, call the unsubscribe script
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    fp = popen(command, "r");
    if (fp == NULL) {
        return 0;
    }

    // Read the output from the command
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Check if the script returned 0
        if (atoi(buffer) == 0) {
            pclose(fp);
            return 1;
        }
    }

    pclose(fp);
    return 0;
}

int main() {
    const char *email = "example@example.com";
    int result = check_email_and_unsubscribe(email);
    printf("Result: %d\n", result);
    return 0;
}