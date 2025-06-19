#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
 
// Function to establish connection with database using mysql_real_connect()
MYSQL* connect_db(char *host, char *user, char *password, const char *dbname) {
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
 
    if (mysql_real_connect(con, host, user, password, dbname, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return NULL;
    }
 
    return con;
}
 
// Function to disconnect from database using mysql_close()
void disconnect_db(MYSQL *con) {
    mysql_close(con);
}
 
// Function to check if the username is valid or not using mysql_query() and mysql_store_result()
int validate_username(char *username, MYSQL *con) {
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s'", username);
 
    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -1;
    }
 
    MYSQL_RES *res = mysql_store_result(con);
    int num_rows = mysql_num_rows(res);
 
    if (num_rows > 0) {
        // Username is valid
        mysql_free_result(res);
        return 1;
    } else {
        // Username is invalid
        mysql_free_result(res);
        return -1;
    }
}
 
// Function to check if the password is correct or not using mysql_query() and mysql_store_result()
int validate_password(char *username, char *password, MYSQL *con) {
    char query[256];
    sprintf(query, "SELECT password FROM users WHERE username='%s'", username);
 
    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -1;
    }
 
    MYSQL_RES *res = mysql_store_result(con);
    int num_rows = mysql_num_rows(res);
 
    if (num_rows > 0) {
        // Password is valid
        MYSQL_ROW row = mysql_fetch_row(res);
        char *dbpassword = row[0];
        if (!strcmp(password, dbpassword)) {
            mysql_free_result(res);
            return 1;
        } else {
            // Password is incorrect
            mysql_free_result(res);
            return -1;
        }
    } else {
        // Username is invalid
        mysql_free_result(res);
        return -1;
    }
}
 
// Function to handle login request using validate_username() and validate_password() functions
void handle_login(char *username, char *password) {
    MYSQL *con = connect_db("localhost", "root", "mypass", "mydatabase");
    if (con == NULL) {
        fprintf(stderr, "Connection failed\n");
        return;
    } else {
        // Connect to database successfully
        int valid_username = validate_username(username, con);
 
        if (valid_username > 0) {
            // Username is valid
            int valid_password = validate_password(username, password, con);
 
            if (valid_password > 0) {
                // Password is correct
                printf("Login successful\n");
                disconnect_db(con);
                return;
            } else {
                // Password is incorrect
                disconnect_db(con);
                return;
            }
        } else {
            // Username is invalid
            disconnect_db(con);
            return;
        }
    }
}
 
int main() {
    char username[256];
    printf("Enter your username: ");
    scanf("%s", username);
 
    char password[256];
    printf("Enter your password: ");
    scanf("%s", password);
 
    handle_login(username, password);
    return 0;
}