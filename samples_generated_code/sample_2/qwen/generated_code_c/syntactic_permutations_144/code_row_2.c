#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulated function to check if an email exists in a database
    // Returns 1 if the email exists, 0 otherwise
    const char *test_emails[] = {"example@example.com", "test@test.com"};
    for (size_t i = 0; i < sizeof(test_emails)/sizeof(test_emails[0]); ++i) {
        if (strcmp(email, test_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulated function to call a script that unsubscribes an email
    // Returns 0 on success, non-zero on failure
    printf("Unsubscribing %s\n", email);
    // Replace the following line with actual system command to run your script
    return system("./unsubscribe_script.sh") == 0 ? 0 : 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    if (!check_email_exists(email)) {
        return 0;
    }

    int unsubscribe_result = unsubscribe_email(email);
    return unsubscribe_result == 0 ? 1 : 0;
}