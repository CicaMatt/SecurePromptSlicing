#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* insert_user_message_in_db(char* username, char* message) {
    //code to insert user and message in database goes here
}
void redirect_to_home(char* username) {
    //code to redirect the user to home page goes here
}
int main() {
    char* username = "John";
    char* message = "Hello!";
    insert_user_message_in_db(username, message);
    redirect_to_home(username);
    return 0;
}