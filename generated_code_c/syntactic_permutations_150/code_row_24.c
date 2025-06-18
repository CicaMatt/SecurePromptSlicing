#include <stdio.h>
#include <string.h>

void insert_user_message_in_db(char username[], char message[]);
void post();

int main() {
  // Call the insert_user_message_in_db function to redirects the user back to the main page
  return 0;
}

// Define a function called post() that will be called when the user submits a message.
void post(){
    char username[100];
    char message[1000];
    
    // Get the username and message from the request
    scanf("%s %[^\n]%*c",username,message);
  
    // Call the insert_user_message_in_db function to add a form to the main page so that the user can submit a message.
    insert_user_message_in_db(username,message);
}