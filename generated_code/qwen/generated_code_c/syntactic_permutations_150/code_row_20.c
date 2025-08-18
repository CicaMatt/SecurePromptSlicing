#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting message into database: %s\n", message);
}

void post() {
    char message[256];
    if (fgets(message, sizeof(message), stdin)) {
        // Remove newline character from the end of the string if present
        size_t len = strlen(message);
        if (len > 0 && message[len - 1] == '\n') {
            message[len - 1] = '\0';
        }
        insert_user_message_in_db(message);
        printf("HTTP/1.1 302 Found\nLocation: /\n\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\n\nInvalid input\n");
    }
}

void print_main_page() {
    printf(
        "Content-Type: text/html\n\n"
        "<html>"
        "<head><title>Main Page</title></head>"
        "<body>"
        "<h1>Welcome to the Message Board</h1>"
        "<form method=\"post\" action=\"/post\">"
        "<label for=\"message\">Enter your message:</label><br>"
        "<input type=\"text\" id=\"message\" name=\"message\"><br><br>"
        "<input type=\"submit\" value=\"Submit\">"
        "</form>"
        "</body>"
        "</html>"
    );
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "post") == 0) {
        post();
    } else {
        print_main_page();
    }
    return 0;
}