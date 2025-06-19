#include <stdio.h>
#include "mylibrary.h"

int main(void) {
    // Get username and message from request
    char *username = get_string("Username: ");
    char *message = get_string("Message: ");
    
    // Call insert_user_message_in_db() function to insert the message in the database
    int result = insert_user_message_in_db(username, message);
    if (result != 0) {
        printf("Error inserting message into database\n");
    }
    
    // Redirect user to main page
    redirect_to_main_page();
    
    return EXIT_SUCCESS;
}