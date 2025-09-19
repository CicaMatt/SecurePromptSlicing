#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_FILE "users.db"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int read_database(User *users, int max_users) {
    FILE *db = fopen(DATABASE_FILE, "r");
    if (!db) return 0;
    int count = 0;
    while (fscanf(db, "%s", users[count].email) == 1 && count < max_users) {
        count++;
    }
    fclose(db);
    return count;
}

int delete_user_from_database(const char *email) {
    User temp[MAX_EMAIL_LENGTH];
    int count = read_database(temp, MAX_EMAIL_LENGTH);

    FILE *db = fopen(DATABASE_FILE, "w");
    if (!db) return 0;

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(temp[i].email, email) == 0) {
            found = 1;
            continue;
        }
        fprintf(db, "%s\n", temp[i].email);
    }

    fclose(db);
    return found;
}

void handle_unsubscribe(const char *email) {
    if (delete_user_from_database(email)) {
        printf("User unsubscribed successfully.\n");
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