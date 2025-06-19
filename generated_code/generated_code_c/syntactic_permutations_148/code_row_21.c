#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to insert message in the database
void insert_message_in_db(char *username, char *message)
{
    // Code to insert message in the database.
}

// Function to display messages on the main page.
void display_messages()
{
    // Code to fetch messages from the database and display them on the main page.
}

// Function to redirect user to the main page after posting a message.
void post()
{
    char username[20];
    char message[100];

    // Get the username and message from the request.
    strcpy(username, get_post_data("username"));
    strcpy(message, get_post_data("message"));

    // Insert user message in database.
    insert_user_message_in_db(username, message);

    // Redirect the user to the main page.
    redirect("/");
}