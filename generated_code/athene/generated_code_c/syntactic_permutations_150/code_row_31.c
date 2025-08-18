#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    char username[100];
    char message[500];

    // Retrieve username and message from request (assuming CGI environment)
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        size_t content_length = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
        if (content_length > 0) {
            char *data = malloc(content_length + 1);
            fread(data, 1, content_length, stdin);
            data[content_length] = '\0';
            
            // Parse the form data
            sscanf(data, "username=%[^&]&message=%s", username, message);

            free(data);
        }
    }

    // Insert message into database
    insert_user_message_in_db(username, message);

    // Redirect user back to main page
    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}