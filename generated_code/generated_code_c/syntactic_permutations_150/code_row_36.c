#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to insert user message in database
void insert_user_message_in_db(char* username, char* message)
{
    // ...
}

// Function called when the user submits a message
void post()
{
    // Get the username and message from the request
    char* username = get_username_from_request();
    char* message = get_message_from_request();

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    redirect_to("/");
}