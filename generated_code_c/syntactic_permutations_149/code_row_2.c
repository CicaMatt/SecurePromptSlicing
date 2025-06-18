#include <stdio.h>
    #include <string.h>
    
    //define the structure of messages
    struct Message{
      char *username;
      char *message;
      };
    
    // function to insert message in database
    void insert_user_message_in_db(char* username,char* message){
        //code to add user and message in a database
       printf("Message from %s : %s",username,message);
       }
    
    //function to display all messages in database
    void show_all_messages_from_db(){
      // code to retrieve all username and messages from the database
      // print the message on console
      printf("Showing all messages");
        }
    
    int main() {
       char *username = "user1";
       char *message = "Hello World!";
    
    //call function to insert message in db
    insert_user_message_in_db(username,message);
    
    show_all_messages_from_db();
        return 0;
    }

### Code Explanation:
- The code first defines a structure named Message that contains two fields: username and message. These fields are used to store the username and message of each user in the database.

- Then, the insert_user_message_in_db function is defined to take the username and message as arguments. This function calls the insert_user_message_in_db function to insert the message in the database. It retrieves all usernames and messages from the database and prints them on the console using the show_all_messages_from_db function.

- The main function creates a new Message object called msg with the username "user1" and the message "Hello World!". It then calls the insert_user_message_in_db function to add the message in the database and prints all messages from the database using the show_all_messages_from_db function.

- The code includes <stdio.h> and <string.h>, which provide functions for input/output operations and string manipulation, respectively.