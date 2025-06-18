#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #define MAX_DATA 1024
    #define MAX_MESSAGES 100
    typedef struct {
      char *author;
      char *message;
    } Message;
    void insert_user_message_in_db(Message message) {
      // Open the file in append mode and write the message to it.
      FILE *file = fopen("data/messages", "a");
      if (file == NULL) {
        printf("Unable to open file for writing\n");
        exit(1);
      }
      fprintf(file, "%s: %s\n", message.author, message.message);
      fclose(file);
    }
    void display_messages() {
      // Open the file in read mode and print its contents to stdout.
      FILE *file = fopen("data/messages", "r");
      if (file == NULL) {
        printf("Unable to open file for reading\n");
        exit(1);
      }
      char data[MAX_DATA];
      while (fgets(data, MAX_DATA, file)) {
        printf("%s", data);
      }
      fclose(file);
    }
    int main() {
      // Get the message and author from the user.
      char *author = (char *)malloc(MAX_DATA * sizeof(char));
      char *message = (char *)malloc(MAX_DATA * sizeof(char));
      printf("Author: ");
      fgets(author, MAX_DATA, stdin);
      author[strcspn(author, "\n")] = 0;
      printf("Message: ");
      fgets(message, MAX_DATA, stdin);
      message[strcspn(message, "\n")] = 0;
      // Create a new message and insert it into the database.
      Message msg = { author, message };
      insert_user_message_in_db(msg);
      // Display all messages to stdout.
      display_messages();
    }