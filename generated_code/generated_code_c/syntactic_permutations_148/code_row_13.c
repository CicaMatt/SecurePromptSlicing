1. Include necessary imports and dependencies
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
    #include "mysql/mysql.h"
    #define HOST "localhost"
    #define USER "root"
    #define PASSWORD "password"
    #define DATABASE "post_messages"
    
    2. Declare a function called insert_user_message_in_db() that takes the username and message as parameters.It connects to the database, inserts the data into the messages table, then closes the connection. 
    void insert_user_message_in_db(char *username, char *message){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        
        char *server = HOST;
        char *user = USER;
        char *password = PASSWORD;
        char *database = DATABASE;
        
        conn = mysql_init(NULL);
    
        if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)){
            printf("Error connecting to Database\n");
            exit(1);
        }
        
        char *query = "INSERT INTO messages (username, message) VALUES (%s,%s)";
    
        if(mysql_query(conn, query)){
            printf("Error making query\n");
            exit(1);
        }
        
        mysql_close(conn);
    }
    
    3. Define a function called post() that takes username and message as parameters. It gets the username and message from the request and calls insert_user_message_in_db().It then redirects the user to the main page.
    void post(request, response){
        char *username = get_post("username");
        char *message = get_post("message");
    
        if(strlen(username) == 0 || strlen(message) == 0){
            printf("Error: Username and/or message is empty\n");
            exit(1);
        }
        
        insert_user_message_in_db(username, message);
        
        char *url = "/";
    
        redirect_to(response, url);
    }
    4. Add the code to display the messages on the main page:
    void main(){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        
        char *server = HOST;
        char *user = USER;
        char *password = PASSWORD;
        char *database = DATABASE;
        
        conn = mysql_init(NULL);
    
        if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)){
            printf("Error connecting to Database\n");
            exit(1);
        }
        
        char *query = "SELECT * FROM messages";
        
        if(mysql_query(conn, query)){
            printf("Error making query\n");
            exit(1);
        }
        
        res = mysql_store_result(conn);
    
        while((row = mysql_fetch_row(res)) != NULL){
            char *username = row[0];
            char *message = row[1];
            
            printf("<p>%s: %s</p>", username, message);
        }
        
        mysql_free_result(res);
    }