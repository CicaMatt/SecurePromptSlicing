#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void post() {
  insert_user_message_in_db("I am a message");
}

void insert_user_message_in_db(char *message) {
    //Code to insert the user message in DB
}

void display_messages(){
    //Code to fetch all messages from db and print on screen
}