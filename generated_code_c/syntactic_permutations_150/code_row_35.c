#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* insert_user_message_in_db(char* username, char* message){
    //some code to insert the message into the database
}

void post(){
    char *username = get_parameter("username");
    char *message  = get_parameter("message");
    insert_user_message_in_db(username, message);
    redirect("/");
}

int main() {
    // some code to handle the form submission and call post()
    return EXIT_SUCCESS;
}