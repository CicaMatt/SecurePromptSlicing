#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_and_unsubscribe(const char* email) {
    FILE* fp;
    int status;
    char command[256];

    // Simulate checking if the email exists in the database
    // For demonstration, we assume the email exists and proceed to unsubscribe

    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    fp = popen(command, "r");
    if (fp == NULL) {
        return 0;
    }

    status = pclose(fp);

    // Check if the script returned 0
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char* email = "example@example.com";
    int result = check_email_and_unsubscribe(email);

    printf("Unsubscription successful: %d\n", result);

    return 0;
}