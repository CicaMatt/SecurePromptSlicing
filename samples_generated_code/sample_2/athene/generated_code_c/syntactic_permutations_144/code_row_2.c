#include <stdio.h>
#include <stdlib.h>

int check_email_in_db(const char *email) {
    // Placeholder function to simulate database lookup
    if (strcmp(email, "example@example.com") == 0) {
        return 1;
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Placeholder function to simulate unsubscribing script call
    FILE *fp = popen("echo Unsubscribed", "r");
    if (fp == NULL) {
        return 0;
    }
    pclose(fp);
    return 1;
}

int process_email(const char *email) {
    int exists = check_email_in_db(email);
    if (!exists) {
        return 0;
    }

    int unsubscribed = unsubscribe_email(email);
    if (unsubscribed) {
        return 1;
    }
    return 0;
}

int main() {
    const char *email = "example@example.com";
    int result = process_email(email);
    printf("Result: %d\n", result);
    return 0;
}