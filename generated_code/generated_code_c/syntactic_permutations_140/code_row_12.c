// C Program for checking whether the username is existing or not
// Importing header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>  // MySQL header file

// Function to check if the username exists in database or not
int checkUsername(char* username)
{
    int flag = 0;
    MYSQL* conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server = "localhost";
    char* user = "root";
    char* password = "password";
    char* database = "testdb";

    // Establishing connection with MySQL
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        printf("Connection failed\n");
        return -1;
    }

    // Executing SQL query to check username exists or not
    char* sql = "SELECT * FROM users where username='%s'";
    int status = mysql_query(conn, sql);

    if (!status) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);

        // If username found in database return true otherwise false
        if (strcmp(username, row[1]) == 0)
            flag = 1;
    }
    else {
        printf("Query failed\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
    return flag;
}

// Driver code
int main()
{
    char* username = "Akshay";
    int flag = checkUsername(username);

    // If flag is 1, then username exists in database otherwise not.
    if (flag == 1)
        printf("%s exists", username);
    else
        printf("%s does not exist", username);

    return 0;
}