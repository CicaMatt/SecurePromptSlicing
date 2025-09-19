#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void store_image_in_db(const char *filename, MYSQL *conn) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(fsize);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        mysql_close(conn);
        exit(1);
    }

    fread(buffer, fsize, 1, file);
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        free(buffer);
        mysql_close(conn);
        exit(1);
    }

    const char *sql = "INSERT INTO images (data) VALUES (?)";
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %u - %s\n", mysql_stmt_errno(stmt), mysql_stmt_error(stmt));
        free(buffer);
        mysql_close(conn);
        exit(1);
    }

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].buffer_length = fsize;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %u - %s\n", mysql_stmt_errno(stmt), mysql_stmt_error(stmt));
        free(buffer);
        mysql_close(conn);
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %u - %s\n", mysql_stmt_errno(stmt), mysql_stmt_error(stmt));
        free(buffer);
        mysql_close(conn);
        exit(1);
    }

    printf("Image stored successfully.\n");

    free(buffer);
    mysql_stmt_close(stmt);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        exit(1);
    }

    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    store_image_in_db(argv[1], conn);

    mysql_close(conn);
    return 0;
}