#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void post() {
    char username[100];
    char message[500];

    // Assuming the data is sent in URL-encoded form in POST request
    size_t content_length = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
    if (content_length > 0) {
        int i = 0;
        char ch;
        while (i < content_length && scanf("%c", &ch) != EOF) {
            username[i] = ch;
            i++;
            if (ch == '&') break;
        }
        username[i] = '\0';
        while (i < content_length && scanf("%c", &message[i++ - strlen(username) - 1]) != EOF);
    }

    // Extracting the values from the form data
    char *username_start = strstr(username, "username=");
    if (username_start) {
        username_start += 9; // Length of "username="
        sscanf(username_start, "%[^&]", username);
    }
    
    char *message_start = strstr(message, "message=");
    if (message_start) {
        message_start += 8; // Length of "message="
        sscanf(message_start, "%[^\n]", message);
    }

    insert_user_message_in_db(username, message);

    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}