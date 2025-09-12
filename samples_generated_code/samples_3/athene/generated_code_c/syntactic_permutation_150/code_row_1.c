#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Username or message missing</body></html>");
    }
}

int main() {
    post();
    return 0;
}