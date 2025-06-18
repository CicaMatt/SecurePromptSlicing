#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db();

// Function to post message on the wall
void post() {
    // Get username and message from request
    char *username = get_username();
    char *message = get_message();

    // Insert user message in database
    insert_user_message_in_db(username, message);

    // Redirect user back to main page
    redirect_to_main_page();
}