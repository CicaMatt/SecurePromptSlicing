#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "your_database"

void upload_pdf(const char *file_path) {
    MYSQL conn;
    MYSQL_STMT *stmt;
    const char *query = "INSERT INTO pdf_files (filepath) VALUES (?)";
    
    // Initialize MySQL connection
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    // Prepare statement
    stmt = mysql_stmt_init(&conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        mysql_close(&conn);
        exit(1);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_close(&conn);
        exit(1);
    }

    // Bind parameters
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    
    char filepath[256] = {0};
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, file_path);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filepath;
    bind[0].buffer_length = strlen(filepath) + 1;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_close(&conn);
        exit(1);
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        mysql_close(&conn);
        exit(1);
    }

    // Clean up
    mysql_stmt_close(stmt);
    mysql_close(&conn);

    printf("PDF file uploaded and saved in the database successfully.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file_name>\n", argv[0]);
        return 1;
    }

    upload_pdf(argv[1]);

    return 0;
}
