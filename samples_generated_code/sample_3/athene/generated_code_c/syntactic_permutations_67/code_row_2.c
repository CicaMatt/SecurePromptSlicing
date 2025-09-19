#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void die_with_error(const char *err) {
    fprintf(stderr, "%s\n", err);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        die_with_error("Usage: ./program image_file");
    }

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        die_with_error("MySQL connection failed");
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        die_with_error("Failed to open image file");
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (fread(buffer, 1, file_size, file) != file_size) {
        die_with_error("Failed to read image file");
    }

    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    char query[256];

    snprintf(query, sizeof(query), "INSERT INTO images (name, data) VALUES (?, ?)");

    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        die_with_error("Statement preparation failed");
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)argv[1];
    bind[0].buffer_length = strlen(argv[1]);

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = buffer;
    bind[1].buffer_length = file_size;

    if (mysql_stmt_bind_param(stmt, bind)) {
        die_with_error("Binding parameters failed");
    }

    if (mysql_stmt_execute(stmt)) {
        die_with_error("Statement execution failed");
    }

    mysql_stmt_close(stmt);
    free(buffer);
    mysql_close(conn);

    return 0;
}