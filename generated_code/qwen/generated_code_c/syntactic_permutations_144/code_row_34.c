#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_and_unsubscribe_email(const char *email) {
    FILE *db = fopen("database.txt", "r");
    if (!db) {
        return 0;
    }

    char line[256];
    int email_found = 0;

    while (fgets(line, sizeof(line), db)) {
        // Remove newline character
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (strcmp(line, email) == 0) {
            email_found = 1;
            break;
        }
    }

    fclose(db);

    if (!email_found) {
        return 0;
    }

    int result = system("./unsubscribe_script.sh");

    return (result == 0);
}

int main() {
    const char *email = "example@example.com";
    int status = check_and_unsubscribe_email(email);
    printf("Status: %d\n", status);
    return 0;
}