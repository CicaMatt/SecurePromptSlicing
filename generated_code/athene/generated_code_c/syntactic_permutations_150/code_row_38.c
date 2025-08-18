#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>You will be redirected shortly.</body></html>");
}

void post() {
    const char *username = getenv("HTTP_USERNAME");
    const char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}