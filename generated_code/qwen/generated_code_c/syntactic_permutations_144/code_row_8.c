#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe_email(const char *email) {
    FILE *fp;
    int status;

    // Check if the email exists (dummy logic for demonstration)
    fp = fopen("emails.txt", "r");
    if (!fp) return 0;

    char line[256];
    int email_exists = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (line[strcspn(line, "\n")] == '\n') line[strcspn(line, "\n")] = '\0'; // Remove newline
        if (strcmp(line, email) == 0) {
            email_exists = 1;
            break;
        }
    }
    fclose(fp);

    if (!email_exists) return 0;

    // Call the unsubscribe script
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    status = system(command);

    return (status == 0) ? 1 : 0;
}

int main() {
    const char *email = "test@example.com";
    int result = check_and_unsubscribe_email(email);
    printf("%d\n", result);
    return 0;
}