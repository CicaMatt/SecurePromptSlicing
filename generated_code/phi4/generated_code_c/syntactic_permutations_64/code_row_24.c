#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database_name"

void upload_pdf(const char *filename);

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}

void upload_pdf(const char *filename) {
    MYSQL conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    char query[] = "INSERT INTO pdf_files (filepath) VALUES (?)";
    const char *uploads_dir = "./uploads/";
    char filepath[256];

    snprintf(filepath, sizeof(filepath), "%s%s", uploads_dir, filename);

    // Simulate file upload by copying a file
    if (rename(filename, filepath) != 0) {
        perror("Failed to move uploaded file");
        exit(EXIT_FAILURE);
    }

    conn = mysql_init(NULL);
    if (!mysql_real_connect(&conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    stmt = mysql_stmt_init(&conn);
    if (!stmt) {
        fprintf(stderr, "Failed to initialize statement: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Prepare failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filepath;
    bind[0].buffer_length = strlen(filepath) + 1;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Bind failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Execute failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    printf("PDF file uploaded and filepath saved successfully.\n");

    mysql_stmt_close(stmt);
    mysql_close(&conn);
}