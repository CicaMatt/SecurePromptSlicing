#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_FILE "users.db"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int read_users(User *users, int max_count) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) return 0;
    
    int count = 0;
    while (fscanf(file, "%255s", users[count].email) == 1 && count < max_count) {
        count++;
    }
    fclose(file);
    return count;
}

int write_users(User *users, int count) {
    FILE *file = fopen(DATABASE_FILE, "w");
    if (!file) return 0;
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", users[i].email);
    }
    fclose(file);
    return 1;
}

void handle_unsubscribe(const char *email) {
    User users[1024];
    int user_count = read_users(users, 1024);

    int found = -1;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Remove the user from the list
        for (int i = found; i < user_count - 1; i++) {
            users[i] = users[i + 1];
        }
        user_count--;

        write_users(users, user_count);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "unsubscribe") != 0) {
        printf("Usage: %s unsubscribe <email>\n", argv[0]);
        return 1;
    }

    handle_unsubscribe(argv[2]);
    return 0;
}