#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void insert_user_message_in_db(const char *message) {
    // Simulate database insertion (not implemented)
    fprintf(stderr, "Message inserted into DB: %s\n", message);
}

void post() {
    char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;
    if (content_length > 0) {
        char *message = malloc(content_length + 1);
        fread(message, 1, content_length, stdin);
        message[content_length] = '\0';
        insert_user_message_in_db(message);
        free(message);
    }
    redirect_to_main_page();
}

void display_messages() {
    // Simulate fetching messages from the database (not implemented)
    const char *messages[] = {"Hello!", "How are you?", "This is a test message."};
    int count = sizeof(messages) / sizeof(messages[0]);

    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    for (int i = 0; i < count; ++i) {
        printf("<p>%s</p>", messages[i]);
    }
    printf("</body></html>");
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }
    return 0;
}