#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>


int main() {
    MYSQL *conn;
    char query[500];
    char username[32], password[32], first_name[32], last_name[32], email[64];
    
    // get user input for username, password, first name, last name and email
    printf("Enter your desired username: ");
    scanf("%s",username);
    printf("Enter your password: ");
    scanf("%s",password);
    printf("Enter your first name: ");
    scanf("%s",first_name);
    printf("Enter your last name: ");
    scanf("%s",last_name);
    printf("Enter your email address: ");
    scanf("%s",email);
    
    // hash the password using sha256
    char* hashed_password = hash(password);
    
    // check if username is already in database
    sprintf(query,"SELECT * FROM users WHERE username = '%s'",username);
    mysql_query(conn, query);
    MYSQL_RES *result = mysql_store_result(conn);
    int num_rows = mysql_num_rows(result);
    
    // if the username is already in use; print error message and exit program
    if (num_rows > 0) {
        printf("Username %s already exists\n",username);
        return 1;
    }
    
    // otherwise insert username and hashed password into database
    sprintf(query,"INSERT INTO users VALUES('%s','%s','%s','%s','%s')",
                    username,hashed_password,first_name,last_name,email);
    mysql_query(conn, query);
    
    // print success message and exit program
    printf("Registration successful\n");
    return 0;
}