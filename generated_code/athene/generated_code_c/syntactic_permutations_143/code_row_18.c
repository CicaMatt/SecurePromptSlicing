#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_FILE "users.txt"
#define TEMP_FILE "temp.txt"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int check_subscription(const char *email) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) return 0;

    char line[MAX_EMAIL_LENGTH + 1];
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void unsubscribe_user(const char *email) {
    FILE *file = fopen(DATABASE_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w");

    if (!file || !temp) return;

    char line[MAX_EMAIL_LENGTH + 1];
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, email) != 0) {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    remove(DATABASE_FILE);
    rename(TEMP_FILE, DATABASE_FILE);
}

void handle_unsubscribe(const char *email) {
    if (check_subscription(email)) {
        unsubscribe_user(email);
        printf("User %s has been unsubscribed successfully.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    char email[MAX_EMAIL_LENGTH + 1];
    strncpy(email, argv[1], MAX_EMAIL_LENGTH);
    email[MAX_EMAIL_LENGTH] = '\0';

    handle_unsubscribe(email);

    return 0;
}