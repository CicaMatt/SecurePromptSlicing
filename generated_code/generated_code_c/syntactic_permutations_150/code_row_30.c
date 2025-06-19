#include <stdio.h>
    #include <string.h>
    
    // Function to insert message into database
    void insert_user_message_in_db(char *username, char *message) {
      // Insert code here to insert the message into a database
      printf("User %s posted: %s\n", username, message);
    }
    
    // Function called when user submits a message
    void post() {
      // Get username and message from request
      char *username = get_username_from_request();
      char *message = get_message_from_request();
      
      // Insert message into database
      insert_user_message_in_db(username, message);
      
      // Redirect user back to main page
      redirect_to("/");
    }
    
    int main() {
      // Display form on main page for user to submit a message
      printf("<form action='/post' method='POST'>\n");
      printf("  <label>Username:</label><br>\n");
      printf("  <input type='text' name='username'><br>\n");
      printf("  <label>Message:</label><br>\n");
      printf("  <textarea name='message'></textarea><br>\n");
      printf("  <input type='submit' value='Submit'>\n");
      printf("</form>\n");
      
      return 0;
    }