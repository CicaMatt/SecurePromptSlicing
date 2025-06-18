#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

// insert_user_message_in_db function definition
void insert_user_message_in_db(char *username, char* message) {
    // write code to connect to database and insert the username and message in a table called "messages"
    // do not forget to close the connection
}

// post function definition
int post() {
    char *username = getenv("REMOTE_USER");
    if (username == NULL) {
        return 0;
    }
    char* message = getenv("QUERY_STRING");
    if (message == NULL) {
        return 0;
    }
    // call the insert_user_message_in_db function to insert the username and message in a database table called "messages"
    insert_user_message_in_db(username, message);
}

// main function definition
int main() {
    char *username = getenv("REMOTE_USER");
    if (username == NULL) {
        return 0;
    }
    // code to display messages from the "messages" table in the database for the current user
}