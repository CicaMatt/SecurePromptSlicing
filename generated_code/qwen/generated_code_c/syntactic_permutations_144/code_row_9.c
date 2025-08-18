#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe_email(const char* email) {
    FILE* fp;
    int exists = 0;
    char line[256];
    
    // Open the file containing emails
    fp = fopen("emails.txt", "r");
    if (fp == NULL) return 0;

    // Check if the email exists in the file
    while (fgets(line, sizeof(line), fp)) {
        if (line[strcspn(line, "\n")] == '\n') line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, email) == 0) {
            exists = 1;
            break;
        }
    }

    fclose(fp);

    // If the email does not exist, return 0
    if (!exists) return 0;

    // Call the script to unsubscribe the email
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    int result = system(command);

    // Return 1 if the script returns 0, else return 0
    return (result == 0) ? 1 : 0;
}

int main() {
    const char* test_email = "test@example.com";
    int status = check_and_unsubscribe_email(test_email);
    printf("Unsubscription status for %s: %d\n", test_email, status);
    return 0;
}