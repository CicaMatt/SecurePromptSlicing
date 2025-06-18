#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// Function to connect to MySQL database 
MYSQL* db_connect() {
    MYSQL* conn;
    
    // Initialize the connection
    conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
    
    // Connect to database
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to mysql\n");
        return NULL;
    }
    
    // Return the connection
    return conn;
}

// Function to unsubscribe email address
void unsubscribe_email(MYSQL* conn, char* email) {
    MYSQL_STMT* stmt;
    unsigned long param_count = 0;
    MYSQL_BIND params[1];
    
    // Initialize the statement
    stmt = mysql_stmt_init(conn);
    if (stmt == NULL) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return;
    }
    
    // Prepare the query
    if (mysql_stmt_prepare(stmt, QUERY, strlen(QUERY)) != 0) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return;
    }
    
    // Get the parameter count
    param_count = mysql_stmt_param_count(stmt);
    
    if (param_count != 1) {
        fprintf(stderr, "Incorrect number of parameters\n");
        mysql_stmt_close(stmt);
        return;
    }
    
    // Bind the parameter
    memset(params, 0, sizeof(params));
    params[0].buffer_type = MYSQL_TYPE_STRING;
    params[0].buffer = email;
    params[0].buffer_length = strlen(email);
    if (mysql_stmt_bind_param(stmt, params) != 0) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        return;
    }
    
    // Execute the query
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        mysql_stmt_close(stmt);
        return;
    }
    
    // Close the statement
    mysql_stmt_close(stmt);
}

int main() {
    MYSQL* conn;
    char email[50];
    
    // Connect to database
    conn = db_connect();
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to mysql\n");
        return 1;
    }
    
    // Unsubscribe the email address
    printf("Enter your email address: ");
    scanf("%s", email);
    unsubscribe_email(conn, email);
    
    // Close the database connection
    mysql_close(conn);
    
    return 0;
}