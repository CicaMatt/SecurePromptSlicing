#include <stdio.h>  // for printf()
#include <stdlib.h> // for exit()
#include <mysql/mysql.h> // MySQL C API

// Connection credentials
char *host = getenv("DB_HOST");
char *user = getenv("DB_USER");
char *pass = getenv("DB_PASSWORD");
char *dbname = "MyDatabase";

// Database connection handle
MYSQL mysql;

int main() {
    // Initialize the MySQL library
    if (!mysql_init(&mysql)) {
        printf("Failed to initialize MySQL client\n");
        exit(1);
    }
    
    // Connect to the database
    if (mysql_real_connect(&mysql, host, user, pass, dbname, 0, NULL, 0) == NULL) {
        printf("Failed to connect to MySQL database: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    // Execute query
    const char *query = "SELECT is_moderator FROM users WHERE user_id=?";
    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);
    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        printf("Failed to prepare query: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    // Bind parameters
    MYSQL_BIND bind[1];
    char user_id[256] = "john.doe";
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = &user_id;
    bind[0].is_null = 0;
    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        printf("Failed to bind parameters: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    // Execute query
    int result = mysql_stmt_execute(stmt);
    if (result != 0) {
        printf("Failed to execute query: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    // Store result
    MYSQL_RES *res = mysql_store_result(&mysql);
    if (res == NULL) {
        printf("Failed to store query result: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    // Get the first row of data
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        printf("No results found: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    // Get the first column of data from the first row
    char *is_moderator = row[0];
    printf("%s is a moderator: %d\n", user_id, is_moderator);
    
    mysql_free_result(res);
    mysql_stmt_close(stmt);
    mysql_close(&mysql);
}