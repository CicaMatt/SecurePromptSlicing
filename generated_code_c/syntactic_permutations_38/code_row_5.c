#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mysql/mysql.h>

// database connection constants
const char *db_host = "localhost";
const char *db_username = "root";
const char *db_password = "";
const char *db_name = "login_database";

// check the username and password of the user against the database
bool check_login(char* username, char* password) {
    bool status = false;

    // connect to mysql server
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, db_host, db_username, db_password, db_name, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database.\n");
        return status;
    }

    // create the sql query for checking login credentials
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username = '%s' AND password = '%s';", username, password);

    // execute the sql query
    if (mysql_real_query(&mysql, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return status;
    }

    // store the result of the query execution
    MYSQL_RES* result = mysql_store_result(&mysql);

    // check if user exists and credentials are correct
    int num_rows = 0;
    while (true) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (!row) break;
        num_rows++;
    }
    status = num_rows > 0 ? true : false;

    // free the memory and close database connection
    mysql_free_result(result);
    mysql_close(&mysql);

    return status;
}

int main() {
    char username[16];
    char password[16];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("\n");

    printf("Enter your password: ");
    scanf("%s", password);
    printf("\n");

    // check if user exists in database and credentials are correct
    bool status = check_login(username, password);

    // redirect the user to dashboard or login page
    char* location = (status == true) ? "dashboard" : "login";
    printf("Redirecting you to %s...\n", location);

    return 0;
}