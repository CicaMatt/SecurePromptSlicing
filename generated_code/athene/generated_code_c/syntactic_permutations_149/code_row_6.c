#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_MESSAGE_LEN 200

typedef struct {
    char username[MAX_USERNAME_LEN];
    char message[MAX_MESSAGE_LEN];
} UserMessage;

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
}

void handle_post_request() {
    char username[MAX_USERNAME_LEN] = "";
    char message[MAX_MESSAGE_LEN] = "";

    // Simulate reading from request (in a real scenario, this would come from HTTP POST data)
    fgets(username, sizeof(username), stdin);
    fgets(message, sizeof(message), stdin);

    // Remove newline characters
    username[strcspn(username, "\n")] = 0;
    message[strcspn(message, "\n")] = 0;

    insert_user_message_in_db(username, message);

    // Redirect to the / route
    printf("Location: /\r\n\r\n");
}

void display_messages() {
    UserMessage messages[] = {
        {"user1", "Hello everyone!"},
        {"user2", "This is a test message."}
    };
    size_t num_messages = sizeof(messages) / sizeof(UserMessage);

    // Display the messages
    printf("<html><body>\n");
    for (size_t i = 0; i < num_messages; ++i) {
        printf("<p><strong>%s:</strong> %s</p>\n", messages[i].username, messages[i].message);
    }
    printf("</body></html>\n");
}

int main() {
    char request_type[10];
    scanf("%s", request_type);

    if (strcmp(request_type, "POST") == 0) {
        handle_post_request();
    } else {
        display_messages();
    }

    return 0;
}