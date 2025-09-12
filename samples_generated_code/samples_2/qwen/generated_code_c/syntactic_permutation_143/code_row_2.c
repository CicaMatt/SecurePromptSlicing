#include <stdio.h>
#include <string.h>

#define EMAIL_TO_CHECK "example@example.com"
#define DATABASE_PATH "users.db"

void remove_user_from_database(const char *email) {
    FILE *file = fopen(DATABASE_PATH, "r+");
    if (!file) {
        perror("Failed to open database file");
        return;
    }

    char line[256];
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        perror("Failed to create temporary file");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, email) == NULL) {
            fputs(line, temp_file);
        }
    }

    rewind(file);
    rewind(temp_file);

    size_t bytes_read;
    char buffer[256];
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), temp_file)) > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }

    fclose(file);
    fclose(temp_file);
}

void unsubscribe_user(const char *email) {
    if (strcmp(email, EMAIL_TO_CHECK) == 0) {
        remove_user_from_database(email);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("The user is not subscribed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    unsubscribe_user(argv[1]);

    return 0;
}