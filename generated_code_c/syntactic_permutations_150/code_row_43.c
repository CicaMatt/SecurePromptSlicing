#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "post.h"

// Adds a user's message into the database.
void insert_user_message_in_db(const char* username, const char* message)
{
    // This is where you would normally add code to interact with your database.
}

int post()
{
    // Get the data from the form.
    char* username = get_form_data("username");
    char* message = get_form_data("message");

    // Insert the user's message into the database.
    insert_user_message_in_db(username, message);

    // Redirect back to the original page.
    redirect();
}