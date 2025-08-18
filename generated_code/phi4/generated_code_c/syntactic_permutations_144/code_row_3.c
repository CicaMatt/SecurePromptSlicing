#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "emails.db"

int check_email_exists(const char *email);
int run_unsubscribe_script(const char *email);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];

    if (!check_email_exists(email)) {
        printf("Email does not exist in the database.\n");
        return 0;
    } else {
        int result = run_unsubscribe_script(email);
        if (result == 0) {
            printf("Failed to unsubscribe email.\n");
            return 0;
        } else {
            printf("Email successfully unsubscribed.\n");
            return 1;
        }
    }
}

int check_email_exists(const char *email) {
    FILE *file = fopen(DB_FILE, "r");
    if (!file) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        if (strcmp(email, line) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int run_unsubscribe_script(const char *email) {
    int result = system("path/to/unsubscribe_script.sh");
    return WEXITSTATUS(result);
}