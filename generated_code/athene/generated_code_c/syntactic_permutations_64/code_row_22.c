#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DATABASE "mydb"
#define TABLE "pdfs"
#define UPLOADS_DIR "./uploads/"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char path[256];
    snprintf(path, sizeof(path), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Failed to open file");
        mysql_close(conn);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    fread(buffer, 1, length, file);
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[3];
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO %s (filename, filedata) VALUES (?, ?)", TABLE);

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, "errno = %d\n", mysql_errno(conn));
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filename;
    bind[0].buffer_length = strlen(filename);

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = buffer;
    bind[1].buffer_length = length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        fprintf(stderr, "errno = %d\n", mysql_errno(conn));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), INSERT failed\n");
        fprintf(stderr, "errno = %d\n", mysql_errno(conn));
        exit(1);
    }

    free(buffer);
    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}