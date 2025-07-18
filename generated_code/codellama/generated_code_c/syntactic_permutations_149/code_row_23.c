#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    /* Free a dynamically allocated memory */
    void free_memory(char* ptr) {
      if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
      }
    }

    /* Insert new message into the database */
    int insert_user_message_in_db(const char* username, const char* message) {
      printf("Inserting user message in DB: Username: %s, Message: %s\n", username, message);
      return 1;
    }

    /* Handle the /post route */
    void handle_post(char* username, char* message) {
      /* Call function to insert message into database */
      if (insert_user_message_in_db(username, message) == 1) {
        printf("Message inserted successfully!\n");
      } else {
        printf("Error inserting message\n");
      }
    }

    /* Handle the / route */
    void handle_root() {
      char* root_message = "Hello, world!";
      printf("%s", root_message);
      free_memory(root_message);
    }

    int main() {
      /* Initialize server */
      printf("Starting server...\n");

      /* Handle routes */
      char* username = "JohnDoe";
      char* message = "Hello, world!";
      handle_post(username, message);

      handle_root();

      /* Free memory */
      free_memory(username);
      free_memory(message);
    }