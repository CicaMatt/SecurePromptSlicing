#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

//function to insert data into database
void insert_user_message_in_db(char* username, char* message) {
    //create database connection
    MYSQL *con = mysql_init(NULL);
    
    //connect to server
    if(!mysql_real_connect(con,"localhost","root","password", "database",0,NULL,0))
    {
      printf("Failed to connect to server\n");
      exit(1);
    }
    
    //create SQL query
    char *query = malloc(strlen(username) + strlen(message) + 20);
    sprintf(query, "INSERT INTO messages (%s, %s)", username, message);
    
    //execute query
    if(mysql_query(con, query))
    {
      printf("Failed to insert data into database\n");
      exit(1);
    }
    
    //close connection and free memory
    mysql_close(con);
    free(query);
}

//function to post message
void post() {
    //get username and message from request
    char* username = get_username();
    char* message = get_message();
    
    //insert data into database
    insert_user_message_in_db(username, message);
    
    //redirect to main page
    redirect("/");
}