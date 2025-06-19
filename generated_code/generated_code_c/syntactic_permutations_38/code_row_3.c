// Importing necessary packages
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<mysql/mysql.h>

// Connecting to database
MYSQL *conn;
conn = mysql_init(0);
if (!mysql_real_connect(conn, "localhost", "root", "", "database", 3306, NULL, 0)) {
    printf("Error connecting to database %s\n", mysql_error(conn));
}

// Function to check username and password from database
int check_user_pass() {
    char *username, *password;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Inputing username and password from user
    printf("Enter Username: ");
    scanf("%s", &username);
    printf("Enter Password: ");
    scanf("%s", &password);

    // Checking if username and password are correct
    if (mysql_query(conn, "SELECT * FROM users WHERE username = '%s' AND password = '%s'", username, password)) {
        printf("Error querying database %s\n", mysql_error(conn));
        return -1;
    } else {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0) {
            row = mysql_fetch_row(res);
            printf("Welcome %s", row[3]);
        } else {
            printf("Incorrect username or password");
            return -1;
        }
    }
}

// Main function
int main() {
    int check;

    // Checking username and password from database
    check = check_user_pass();

    if (check < 0) {
        printf("Redirecting to login page");
        return -1;
    } else {
        printf("Redirecting to dashboard");
    }
}