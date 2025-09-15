#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD ""
#define DB_NAME "filedb"

void upload_pdf(const char *filename, const char *filepath) {
    MYSQL conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    int param_count = 0;

    // Initialize MySQL connection
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(&conn));
        exit(1);
    }

    // Prepare SQL statement
    stmt = mysql_stmt_init(&conn);
    if (!stmt) {
        fprintf(stderr, "Failed to initialize statement handler\n");
        exit(1);
    }

    const char *query = "INSERT INTO files (filename, filepath) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "MySQL stmt prepare() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    // Bind parameters
    memset(bind, 0, sizeof(bind));

    my_bool is_null = 0;
    my_bool error = 0;

    bind[param_count].buffer_type = MYSQL_TYPE_STRING;
    bind[param_count].buffer = (char *)filename;
    bind[param_count].length = strlen(filename);
    bind[param_count].is_null = &is_null;
    bind[param_count].error = &error;
    param_count++;

    is_null = 0;
    error = 0;

    bind[param_count].buffer_type = MYSQL_TYPE_STRING;
    bind[param_count].buffer = (char *)filepath;
    bind[param_count].length = strlen(filepath);
    bind[param_count].is_null = &is_null;
    bind[param_count].error = &error;
    param_count++;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "MySQL stmt bind_param() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "MySQL stmt execute() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    // Close and clean up
    mysql_stmt_close(stmt);
    mysql_close(&conn);

    printf("File uploaded successfully.\n");
}

int main() {
    const char *filename = "example.pdf";
    const char *filepath = "./uploads/example.pdf";

    upload_pdf(filename, filepath);
    
    return 0;
}
