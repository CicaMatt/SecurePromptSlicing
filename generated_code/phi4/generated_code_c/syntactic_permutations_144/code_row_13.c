#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "emails.db"

int check_email_exists(const char *email) {
    FILE *file = fopen(DB_FILE, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int run_unsubscribe_script(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "unsubscribe_script.sh %s", email);

    int result = system(command);
    return WEXITSTATUS(result) == 1 ? 1 : 0;
}

void handle_email(const char *email) {
    if (!check_email_exists(email)) {
        printf("Email does not exist in the database.\n");
    } else {
        if (run_unsubscribe_script(email)) {
            printf("Unsubscribed successfully.\n");
        } else {
            printf("Failed to unsubscribe.\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_email(argv[1]);

    return EXIT_SUCCESS;
}