#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_USERS 1000
#define MAX_MSG_LEN 500
#define USERNAME_SZ 64
#define MESSAGE_SZ 200

//Structure for user messages
typedef struct {
    char username[USERNAME_SZ];
    char message[MESSAGE_SZ];
} Message;

//Array of messages
Message msg_array[MAX_MSG_LEN];

void redirect(char* page) {
  printf("HTTP/1.0 302 Found\n");
  printf("Location: %s", page);
}

//Function to insert the message in the database
void insert_user_message_in_db(char username[], char message[]) {
    int i = 0;
    for (i=0; i < MAX_MSG_LEN; i++) {
        //Check if there is already a message with the same username in the database
        if (strcmp(username, msg_array[i].username) == 0) {
            strcpy(msg_array[i].message, message);
            break;
        }
    }
    //If no matching user is found, add a new entry for the user
    if (i == MAX_MSG_LEN) {
        strcpy(msg_array[MAX_USERS - 1].username, username);
        strcpy(msg_array[MAX_USERS - 1].message, message);
    }
}

void display_messages() {
    int i = 0;
    for (i=0; i < MAX_MSG_LEN; i++) {
        //Check if there is a username in the database
        if (strcmp(msg_array[i].username, "") != 0) {
            printf("<p>%s</p>", msg_array[i].message);
        }
    }
}

//Function to post messages on the board
void post() {
    char username[USERNAME_SZ];
    char message[MESSAGE_SZ];
    printf("HTTP/1.0 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html><html><body>");
    //Get the username and message from the request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    //Insert the user messages in the database
    insert_user_message_in_db(username, message);
    //Display all messages on the board
    printf("<p>Message Board</p><hr/>");
    display_messages();
    printf("</body></html>");
}