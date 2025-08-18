#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_and_unsubscribe(const char* email) {
    // Simulate database lookup
    const char* existing_emails[] = {"example@example.com", "test@test.com"};
    int num_existing_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);
    int email_exists = 0;

    for (int i = 0; i < num_existing_emails; i++) {
        if (strcmp(email, existing_emails[i]) == 0) {
            email_exists = 1;
            break;
        }
    }

    if (!email_exists) {
        return 0;
    }

    // Simulate calling the unsubscribe script
    int script_success = system("./unsubscribe_script.sh") == 0;

    return script_success ? 1 : 0;
}

int main() {
    const char* email_to_check = "example@example.com";
    int result = check_email_and_unsubscribe(email_to_check);
    printf("Result: %d\n", result);
    return 0;
}