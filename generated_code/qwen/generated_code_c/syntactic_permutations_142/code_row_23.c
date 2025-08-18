#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_PATH "email_list.txt"

int email_exists(const char *email) {
    FILE *file = fopen(DATABASE_PATH, "r");
    if (!file) return 0;

    char line[MAX_EMAIL_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void remove_email(const char *email) {
    FILE *file = fopen(DATABASE_PATH, "r");
    if (!file) return;

    FILE *temp_file = fopen("temp_list.txt", "w");
    if (!temp_file) {
        fclose(file);
        return;
    }

    char line[MAX_EMAIL_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (strcmp(line, email) != 0) {
            fprintf(temp_file, "%s\n", line);
        }
    }

    fclose(file);
    fclose(temp_file);

    // Replace the original file with the new one
    remove(DATABASE_PATH);
    rename("temp_list.txt", DATABASE_PATH);
}

void unsubscribe(const char *email) {
    if (email_exists(email)) {
        remove_email(email);
        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("Email address not found. You are not subscribed.\n");
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin)) {
        // Remove newline character if present
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    }
    return 0;
}