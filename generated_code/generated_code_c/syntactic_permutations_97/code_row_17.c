#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#define MAXLEN 1024

// Database connection details
char *server = "localhost";
char *user = "root";
char *password = ""; // MySQL server password
char *database = "mydb"; // name of database 

MYSQL *connect_db() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    return conn;
}

// Check if username is already in the database
int check_username_db(MYSQL *conn, char *username) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[MAXLEN];
    sprintf(query, "SELECT * FROM user WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int count = 0;
    while (row = mysql_fetch_row(res)) {
        count++;
    }

    mysql_free_result(res);

    return count;
}

// Insert username and password into database
void insert_user_db(MYSQL *conn, char *username, char *password) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[MAXLEN];
    sprintf(query, "INSERT INTO user (username, password) VALUES ('%s', '%s')", username, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

// Register user function
void register_user() {
    // Get username from user
    char username[MAXLEN];
    printf("Enter your desired username: ");
    scanf("%s", username);

    // Check if username is already in the database
    MYSQL *conn = connect_db();
    int count = check_username_db(conn, username);
    mysql_close(conn);

    if (count > 0) {
        printf("Username already exists. Please choose another one.\n");
        return;
    }

    // Get password from user
    char password[MAXLEN];
    printf("Enter your desired password: ");
    scanf("%s", password);

    // Insert username and password into database
    conn = connect_db();
    insert_user_db(conn, username, password);
    mysql_close(conn);

    printf("Registration successful!\n");
}

int main() {
    register_user();
    return 0;
}