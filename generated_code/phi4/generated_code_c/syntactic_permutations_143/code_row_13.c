#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILE "users.db"
#define UNSUBSCRIBE_MESSAGE "User unsubscribed successfully.\n"
#define NOT_SUBSCRIBED_MESSAGE "User is not subscribed.\n"

typedef struct {
    char email[100];
} User;

int read_database(User **users) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) return 0;

    int count = 0;
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char *data = (char*)malloc(fsize + 1);
    fread(data, 1, fsize, file);
    data[fsize] = '\0';
    
    const char *delimiter = "\n";
    char *token = strtok(data, delimiter);
    while (token) {
        count++;
        token = strtok(NULL, delimiter);
    }

    if (!count) {
        free(data);
        fclose(file);
        return 0;
    }

    *users = (User *)malloc(sizeof(User) * count);

    fseek(file, 0, SEEK_SET);
    int i = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        strncpy((*users)[i].email, line, sizeof((*users)[i].email));
        (*users)[i].email[strcspn((*users)[i].email, "\n")] = '\0'; // Remove newline
        i++;
    }
    
    free(data);
    fclose(file);
    return count;
}

int remove_user(User **users, int *count, const char *target_email) {
    for (int i = 0; i < *count; ++i) {
        if (strcmp((*users)[i].email, target_email) == 0) {
            memmove(&(*users)[i], &(*users)[i + 1], (*count - i - 1) * sizeof(User));
            --*count;
            return 1;
        }
    }
    return 0;
}

void write_database(User *users, int count) {
    FILE *file = fopen(DATABASE_FILE, "w");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s\n", users[i].email);
    }
    fclose(file);
}

void handle_unsubscribe(const char *email_to_remove) {
    User *users = NULL;
    int user_count = read_database(&users);

    if (user_count == 0) {
        printf(NOT_SUBSCRIBED_MESSAGE);
        return;
    }

    if (remove_user(&users, &user_count, email_to_remove)) {
        write_database(users, user_count);
        printf(UNSUBSCRIBE_MESSAGE);
    } else {
        printf(NOT_SUBSCRIBED_MESSAGE);
    }
    
    free(users);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email_to_unsubscribe>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_unsubscribe(argv[1]);
    return EXIT_SUCCESS;
}