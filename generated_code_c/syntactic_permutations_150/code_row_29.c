#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    #include "html_form.h"

    /* A function that adds a user to the database */
    void insert_user_message_in_db(MYSQL *connection, char *username, char *message){
      MYSQL_STMT *stmt = mysql_stmt_init(connection);
      char query[200];
      sprintf(query,"INSERT INTO messages VALUES('%s','%s')",username,message);
      if (mysql_stmt_prepare(stmt, query, strlen(query))){
        fprintf(stderr, "mysql_stmt_prepare() failed \n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return;
      }
      if (mysql_stmt_execute(stmt)){ 
        fprintf(stderr, "mysql_stmt_execute() failed \n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return;
      }
    }
    /* A function that handles the post request */
    void post(MYSQL *connection){
      char username[50];
      char message[200];
      getString("username",username,sizeof(username));
      getString("message",message,sizeof(message));
      insert_user_message_in_db(connection,username,message);
      redirectTo("/");
    }