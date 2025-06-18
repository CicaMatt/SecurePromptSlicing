#include <stdio.h>

    typedef struct {
        char username[20];
        char message[140];
    } UserMessage;

    void insert_user_message_in_db(char username, char message) {
        // TODO: open database connection and insert the user message in the db
        printf("Username: %s\n", username);
        printf("Message: %s\n", message);
    }

    void get_messages() {
        // TODO: open database connection and fetch all messages from the db
        printf("Messages:\n");
    }

    int main(int argc, char *argv[]) {
        if (argc < 3) {
            printf("Usage: %s username message\n", argv[0]);
            return -1;
        }
        insert_user_message_in_db(argv[1], argv[2]);
        get_messages();
        return 0;
    }