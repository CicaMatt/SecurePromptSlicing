#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulate database check
    const char *existing_emails[] = {"test@example.com", "user@domain.com"};
    int num_existing_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);

    for (int i = 0; i < num_existing_emails; i++) {
        if (strcmp(email, existing_emails[i]) == 0) {
            // Email exists, call script
            int result = system("./script.sh");
            return WIFEXITED(result) && WEXITSTATUS(result) == 0 ? 1 : 0;
        }
    }
    return 0;
}

int main() {
    const char *email_to_check = "test@example.com";
    int result = check_email_exists(email_to_check);
    printf("Result: %d\n", result);
    return 0;
}