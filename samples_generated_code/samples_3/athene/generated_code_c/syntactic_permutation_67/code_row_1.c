#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void fatal(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image file>\n", argv[0]);
        return 1;
    }

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fatal("Failed to connect to database");
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fatal("Failed to open file");
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    unsigned char *data = malloc(size);
    if (fread(data, 1, size, file) != size) {
        fclose(file);
        mysql_close(conn);
        fatal("Failed to read file");
    }
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    my_bool is_null = FALSE;
    unsigned long length;

    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, "INSERT INTO images (data) VALUES (?)", -1)) {
        fatal("Failed to prepare statement");
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = data;
    bind[0].buffer_length = size;
    bind[0].is_null = &is_null;
    bind[0].length = &length;

    length = size;
    if (mysql_stmt_bind_param(stmt, bind)) {
        fatal("Failed to bind parameters");
    }

    if (mysql_stmt_execute(stmt)) {
        fatal("Failed to execute statement");
    }

    mysql_stmt_close(stmt);
    free(data);
    mysql_close(conn);

    return 0;
}