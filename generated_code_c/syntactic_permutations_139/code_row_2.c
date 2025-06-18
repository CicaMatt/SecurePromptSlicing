// Importing necessary header files
#include <stdio.h>
#include <stdlib.h>
#include<mysql/mysql.h>
  
// Function to check if user is Moderator or not
int check_user(const char *username) {
    // Setting up database connection
    MYSQL mysql;
    mysql_init(&mysql);
    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *dbname = getenv("DB_NAME");
    mysql_real_connect(&mysql, host, user, password, dbname, 0, NULL, 0);
  
    // Checking if connection is successful or not
    if (mysql_error(&mysql)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
    }
  
    // Preparing SQL query for checking user status
    const char *sql = "SELECT COUNT(*) FROM Moderators WHERE username = %s";
    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);
    int is_moderator;
  
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }
  
    // Binding the username parameter to SQL query
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    const char *username = "admin";
    char *ptr = (char *)&username;
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = ptr;
    bind[0].length = &username_len;
  
    // Executing the query and getting result
    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }
  
    // Getting result from the query
    MYSQL_BIND result;
    int count = 0;
    memset(&result, 0, sizeof(result));
    result.buffer_type = MYSQL_TYPE_LONG;
    result.buffer = &count;
  
    if (mysql_stmt_bind_result(stmt, &result)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }
    while (mysql_stmt_fetch(stmt) != MYSQL_NO_DATA) {
        printf("Count : %d\n", count);
    }
  
    // Closing the database connection
    mysql_close(&mysql);
    return is_moderator;
}