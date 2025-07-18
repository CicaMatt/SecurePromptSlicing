#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void post(char* username, char* message) {
    insert_user_message_in_db(username, message);
    redirect_to("/display-messages");
}