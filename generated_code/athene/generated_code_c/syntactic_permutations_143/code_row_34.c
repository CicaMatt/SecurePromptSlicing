#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254
#define DATABASE_FILE "users.db"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int email_exists(const char *email) {
    FILE *db = fopen(DATABASE_FILE, "r");
    if (!db) return 0;

    User user;
    while (fscanf(db, "%253s", user.email) == 1) {
        if (strcmp(user.email, email) == 0) {
            fclose(db);
            return 1;
        }
    }

    fclose(db);
    return 0;
}

void remove_user(const char *email) {
    FILE *db = fopen(DATABASE_FILE, "r");
    if (!db) return;

    FILE *temp_db = fopen("temp.db", "w");
    User user;
    while (fscanf(db, "%253s", user.email) == 1) {
        if (strcmp(user.email, email) != 0) {
            fprintf(temp_db, "%s\n", user.email);
        }
    }

    fclose(db);
    fclose(temp_db);

    remove(DATABASE_FILE);
    rename("temp.db", DATABASE_FILE);
}

void handle_unsubscribe(const char *email) {
    if (email_exists(email)) {
        remove_user(email);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User is not subscribed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    handle_unsubscribe(email);

    return 0;
}