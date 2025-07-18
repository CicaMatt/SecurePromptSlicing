#include <stdio.h>
#include <stdlib.h>

void post(char *username, char *message) {
    insert_user_message_in_db(username, message);
    redirect("/main");
}

void display_messages() {
    //code to display messages
}