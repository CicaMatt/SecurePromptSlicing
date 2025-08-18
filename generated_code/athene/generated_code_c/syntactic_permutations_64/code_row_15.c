#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"
#define DB_HOST "localhost"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    const char *sql = "INSERT INTO pdf_files (filename, data) VALUES (?, ?)";
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "SQL Statement preparation failed: %s\n", mysql_error(conn));
        exit(1);
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filename;
    bind[0].length = 0;

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = buffer;
    bind[1].length = file_size;

    mysql_stmt_bind_param(stmt, bind);
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Failed to execute statement: %s\n", mysql_error(conn));
        exit(1);
    }

    printf("File uploaded successfully.\n");

    mysql_stmt_close(stmt);
    mysql_close(conn);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        exit(1);
    }

    upload_pdf(argv[1]);

    return 0;
}