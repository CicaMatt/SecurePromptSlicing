#include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <mysql/mysql.h>

   void insert_user_message_in_db(char *username, char *message){
        MYSQL mysql;
        mysql_init(&mysql);
        if (mysql_real_connect(&mysql, "localhost", "root", "password", "mydb", 3306, NULL, 0)){
                const char *query = "INSERT INTO mytable(username,message) VALUES(%s,%s)";
                MYSQL_STMT *stmt = mysql_stmt_init(&mysql);
                if (stmt != NULL){
                        if (mysql_stmt_prepare(stmt, query, strlen(query))){
                                const char *msg = "Error preparing statement";
                                fprintf(stderr, "%s\n", msg);
                                free((void*)msg);
                                mysql_close(&mysql);
                        }else{
                                MYSQL_BIND params[2];
                                memset(params, 0, sizeof(params));
                                char *username_param = username;
                                char *message_param = message;
                                params[0].buffer_type = MYSQL_TYPE_STRING;
                                params[0].buffer = (void*) username_param;
                                params[1].buffer_type = MYSQL_TYPE_STRING;
                                params[1].buffer = (void*) message_param;
                                if(mysql_stmt_bind_param(stmt, params)){
                                        const char *msg = "Error binding parameters";
                                        fprintf(stderr, "%s\n", msg);
                                        free((void*)msg);
                                        mysql_close(&mysql);
                                }else{
                                        if (mysql_stmt_execute(stmt)){
                                                const char *msg = "Error executing prepared statement";
                                                fprintf(stderr, "%s\n", msg);
                                                free((void*)msg);
                                                mysql_close(&mysql);
                                        }else{
                                                printf("Message inserted successfully");
                                        }
                                }
                                mysql_stmt_close(stmt);
                        }
                }
        }
    }
    
   void post(char *username, char *message){
       insert_user_message_in_db(username, message);
       redirect_to_main();
   }

   void main(){
       printf("Welcome to my chat app");
       printf("Enter your name: ");
       char username[20];
       scanf("%s", &username);
       printf("Hello %s\n", username);
       printf("Enter message: ");
       char message[50];
       scanf("%s", &message);
       post(username, message);
   }

### Explanation:
This code defines a function called insert_user_message_in_db that takes in two strings as parameters. It first connects to the mydb database using the root user with a password of “password”. Then it creates an SQL query to insert the username and message into a table called mytable. Next, it initializes a statement object and prepares the query. Finally, it binds the input parameters to the statement object and executes it.

The post function takes in two strings as parameters and calls the insert_user_message_in_db function with them. It then redirects the user back to the main page. The main function asks for a username and message from the user, passes those values to the post function, and prints a success message.