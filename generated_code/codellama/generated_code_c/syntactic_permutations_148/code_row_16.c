#include <stdio.h>

    void post(char *username, char *message) {
        /* Insert message into database */
        insert_user_message_in_db(username, message);
        /* Redirect user to main page */
        redirect("/");
    }

    int main() {
        /* Display messages */
        display_messages();
    }