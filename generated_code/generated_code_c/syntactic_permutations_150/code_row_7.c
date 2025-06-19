#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 //Define insert_user_message_in_db() function
 
 void insert_user_message_in_db(const char *username, const char *message){
    printf("Inserting %s's message: %s into the database\n", username, message);
 }
 //Define post() function
 
 void post(const char *username, const char *message){
    insert_user_message_in_db(username, message);
 }
 //Calling post() function
 
 int main(){
    post("John", "Hello");
    return 0;
 }