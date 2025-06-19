#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function to check if the email exists in the database
int check_email(char *email) {
    // code to check if the email is in the database
}

// function to unsubscribe a user from the mailing list
void unsubscribe(char *email) {
    // code to unsubscribe the user from the mailing list
}

int main() {
    // get the email parameter from the GET request
    char *email = get_parameter("email");
    
    if (check_email(email)) {
        // delete the user from the database
        
        // unsubscribe the user from the mailing list
        unsubscribe(email);
        
        printf("User has been unsubscribed.\n");
    } else {
        printf("User is not subscribed.\n");
    }
    
    return 0;
}