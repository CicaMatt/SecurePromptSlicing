#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void insert_user_message_in_db(char *username, char *message) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int qstate;
    
    mysql_init(&conn);
    
    if (!mysql_real_connect(&conn, "localhost", "root", "password", "messages", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return;
    }
    
    const char *query = "INSERT INTO messages (username, message) VALUES (?, ?);";
    
    MYSQL_STMT *stmt = mysql_stmt_init(&conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return;
    }
    
    qstate = mysql_stmt_prepare(stmt, query, strlen(query));
    if (qstate) {
        fprintf(stderr, "mysql_stmt_prepare() failed with: %s\n", mysql_stmt_error(stmt));
        return;
    }
    
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));
    
    char username_buff[16], message_buff[256];
    
    strncpy(username_buff, username, 16);
    strncpy(message_buff, message, 256);
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = username_buff;
    bind[0].buffer_length = 16;
    
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = message_buff;
    bind[1].buffer_length = 256;
    
    mysql_stmt_bind_param(stmt, bind);
    
    qstate = mysql_stmt_execute(stmt);
    if (qstate) {
        fprintf(stderr, "mysql_stmt_execute() failed with: %s\n", mysql_stmt_error(stmt));
        return;
    }
}

void post(char *username, char *message) {
    insert_user_message_in_db(username, message);
    header("Location: index.html");
}