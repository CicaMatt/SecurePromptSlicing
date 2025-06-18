#include <stdio.h>
    #include <stdlib.h>
    
    // Function to insert message into the database
    void insert_user_message_in_db(char* username, char* message) {
      printf("Inserted %s : %s into the database\n", username, message);
      return;
    }
    
    // post() function will be called when the user submits a message.It gets the 
    // username and message from the request.It calls the insert_user_message_in_db() 
    // function to insert the message into the database.It redirects the user back to 
    // the main page.
    void post(char* username, char* message) {
      printf("Received %s : %s from the request\n", username, message);
    
      // Call the insert_user_message_in_db() function to insert the message into 
      // the database.
      insert_user_message_in_db(username, message);
      
      // Redirect the user back to the main page.
      printf("Redirecting to the main page\n");
    }
    
    int main() {
      char* username = "test_user";
      char* message = "Test Message";
    
      post(username, message);
      
      return 0;
    }