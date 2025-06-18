#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include <mysql/mysql.h> // MySQL header file

// Global variables
char *username, *password;
const char* hostname = "localhost";
const char* db_name = "login";
const char* user = "root";
const char* password = "";
bool isAuthenticated = false;

// MySQL connection object
//MYSQL mysql;

void main(){
    // Connect to database
   // if (mysql_real_connect(&mysql, hostname, user, password, db_name, 0, NULL, 0)) {
        // printf("Connection success!\n");

        // Ask for username and password
        printf("Enter Username: ");
        scanf("%s", &username);
        printf("Enter Password: ");
        scanf("%s", &password);

        // Check if the username and password are in the database
        //char *query = "SELECT * FROM users WHERE username=? AND password=?";
       // MYSQL_STMT *stmt;
       // MYSQL_BIND params[2];

       // stmt = mysql_stmt_init(&mysql);
       // if (mysql_stmt_prepare(stmt, query, strlen(query))) {
       //     printf("Error preparing statement\n");
       //     exit(1);
       // }

       // memset(params, 0, sizeof(params));
       // params[0].buffer_type = MYSQL_TYPE_STRING;
       // params[0].buffer = username;
       // params[0].length = strlen(username);
       // params[1].buffer_type = MYSQL_TYPE_STRING;
       // params[1].buffer = password;
       // params[1].length = strlen(password);

       // if (mysql_stmt_bind_param(stmt, params)) {
       //     printf("Error binding parameters\n");
       //     exit(1);
       // }

       // if (mysql_stmt_execute(stmt)) {
       //     printf("Error executing query\n");
       //     exit(1);
       // }

        // Check for results
        //MYSQL_RES *result = mysql_store_result(&mysql);
        //if (mysql_num_rows(result) > 0) {
            // Redirect to welcome page
         //   isAuthenticated = true;
       // } else {
            // Redirect to can't login page
      //  }

        // Close the statement
        //mysql_stmt_close(stmt);
    //} else {
        // Redirect to internal server error page
     //   printf("Error connecting to database\n");
       // exit(1);
   // }
//}

int main()
{
    char username[50], password[50];
    int auth;
    printf("Enter username: ");
    scanf("%s",username);
    printf("Enter password: ");
    scanf("%s",password);

    if(strcmpi(username,"admin")==0 && strcmpi(password,"admin")==0){
        printf("Access granted!");
        auth = 1;
    }else{
        printf("Wrong username or password!");
        auth = 0;
    }
return 0;
}