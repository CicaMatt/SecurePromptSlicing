#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "rb");
    if (!file) error_exit("Error opening image file");

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);

    buffer[fsize] = '\0';

    MYSQL *conn;
    MYSQL_STMT *stmt;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        error_exit("MySQL connection failed");
    }

    const char *query = "INSERT INTO images (image_data) VALUES (?)";
    stmt = mysql_stmt_init(conn);
    if (!stmt) error_exit("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    MYSQL_BIND bind[1];
    my_bool is_null = 0;
    unsigned long length = fsize;

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = (char *)buffer;
    bind[0].is_null = &is_null;
    bind[0].length = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    free(buffer);
    return 0;
}