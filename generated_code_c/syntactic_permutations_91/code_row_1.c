#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>

/* User account registration */
void register_user(char *username, char *password) {
    /* Create a connection to the database */
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(conn, "localhost", "root", "password", "mydatabase", 0, NULL, 0)) {
        fprintf(stdout, "Connected to database\n");
    } else {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(conn));
        exit(1);
    }
    
    /* Prepare the SQL query */
    char sql[256];
    sprintf(sql, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, password);
    
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "Failed to execute SQL query: %s\n", mysql_error(conn));
    } else {
        fprintf(stdout, "User registered successfully\n");
    }
    
    /* Close the connection to the database */
    mysql_close(conn);
}

int main() {
    char username[32];
    char password[16];
    
    printf("Enter a username: ");
    fgets(username, sizeof(username), stdin);
    strtok(username, "\n");
    
    printf("Enter a password: ");
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n");
    
    register_user(username, password);
    return 0;
}