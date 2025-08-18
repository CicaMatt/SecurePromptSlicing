#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD ""
#define DB_DATABASE "mydatabase"

void upload_pdf(const char *filename) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    my_bool is_null = 0;
    int length;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "INSERT INTO pdf_files (filepath) VALUES (?)";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Failed to initialize statement\n");
        mysql_close(conn);
        exit(1);
    }
    
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Failed to prepare statement: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(1);
    }

    const char *filepath = "./uploads/";
    length = snprintf(NULL, 0, "%s%s", filepath, filename) + 1;
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = malloc(length);
    bind[0].buffer_length = length;
    bind[0].length = &length;
    bind[0].is_null = &is_null;

    snprintf((char *)bind[0].buffer, length, "%s%s", filepath, filename);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Failed to bind parameters: %s\n", mysql_stmt_error(stmt));
        free(bind[0].buffer);
        mysql_close(conn);
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Execution failed: %s\n", mysql_stmt_error(stmt));
        free(bind[0].buffer);
        mysql_close(conn);
        exit(1);
    }

    printf("PDF uploaded successfully.\n");

    mysql_stmt_close(stmt);
    mysql_close(conn);
    free(bind[0].buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    upload_pdf(argv[1]);

    return 0;
}