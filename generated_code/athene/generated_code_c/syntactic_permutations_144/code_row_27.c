#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    // Simulate database check (0 = does not exist, 1 = exists)
    if (strcmp(email, "example@example.com") == 0) {
        return 1;
    }
    return 0;
}

int unsubscribeEmailScript(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main() {
    const char *email = "example@example.com";
    if (!checkEmailInDatabase(email)) {
        printf("Email does not exist in the database.\n");
        return 0;
    }

    int result = unsubscribeEmailScript(email);
    if (result == 1) {
        printf("Unsubscribed successfully.\n");
    } else {
        printf("Failed to unsubscribe.\n");
    }
    return result;
}