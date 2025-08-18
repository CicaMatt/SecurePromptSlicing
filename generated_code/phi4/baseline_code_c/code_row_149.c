#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PATH "messages.db"

typedef struct {
    char username[50];
    char message[256];
} UserMessage;

void insert_user_message_in_db(const char *username, const char *message) {
    FILE *db = fopen(DB_PATH, "a");
    if (db == NULL) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s,%s\n", username, message);
    fclose(db);
}

void display_messages() {
    FILE *db = fopen(DB_PATH, "r");
    if (db == NULL) {
        perror("Failed to open database file");
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), db)) {
        printf("%s", buffer);
    }
    fclose(db);
}

void handle_post_request(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to /...\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s username message\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    const char *message = argv[2];

    handle_post_request(username, message);
    
    printf("Messages:\n");
    display_messages();

    return 0;
}