#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
#include "cgi_functions.h"

char* insert_user_message_in_db(MYSQL *connect, char* username, char* message){
    // check if the user already exists in database and fetch the userid
    char query[255];
    sprintf(query, "SELECT id FROM users WHERE username = '%s'", username);
    MYSQL_RES *res = mysql_store_result(connect);
    int num_rows = mysql_num_rows(res);

    if (num_rows > 0){
        // user exists, so update the message in database
        char* userid = mysql_fetch_row(res)[0];
        sprintf(query, "UPDATE users SET message = '%s' WHERE id = %s", message, userid);
    } else {
        // user doesn't exist, so insert the username and message in database
        sprintf(query, "INSERT INTO users (username, message) VALUES ('%s', '%s')", username, message);
    }
    if (mysql_query(connect, query)){
        printf("Error: %s\n", mysql_error(connect));
    }
    return 0;
}

int main(){
    // get the form data from cgi_functions library
    char* username = get_form_value("username");
    char* message = get_form_value("message");

    // check if there was a post request and message is not empty
    if (strlen(message) > 0){
        // connect to database
        MYSQL *connect = mysql_init(NULL);
        char* host = "localhost";
        char* user = "root";
        char* pass = "";
        char* dbname = "messages";
        if (mysql_real_connect(connect, host, user, pass, dbname, 0, NULL, 0) == NULL){
            printf("Error: %s\n", mysql_error(connect));
            return 1;
        }

        // call the insert_user_message_in_db function
        insert_user_message_in_db(connect, username, message);
    }

    // display all messages from database
    char* html = "<html><head><title>Messages</title></head><body>";
    html += "<h1>Welcome to Messages!</h1>";
    html += "<ul>";
    mysql_query(connect, "SELECT * FROM users");
    MYSQL_RES *res = mysql_store_result(connect);
    while (MYSQL_ROW row = mysql_fetch_row(res)){
        char* username = row[0];
        char* message = row[1];
        html += "<li>%s: %s</li>", username, message;
    }
    html += "</ul>";
    html += "</body></html>";
    printf("Content-type: text/html\n");
    printf("\r\n"); // blank line between headers and content, very important !
    printf("%s", html);
    mysql_close(connect);
    return 0;
}