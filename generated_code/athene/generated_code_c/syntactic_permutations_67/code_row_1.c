#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void store_image_in_db(const char *filename, MYSQL *conn) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(length);
    if (fread(buffer, 1, length, file) != length) {
        fprintf(stderr, "Could not read file %s\n", filename);
        exit(1);
    }
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO images (filename, data) VALUES (?, ?)");

    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Could not prepare statement\n");
        exit(1);
    }

    bind[0].buffer_type  = MYSQL_TYPE_STRING;
    bind[0].buffer       = (char *)filename;
    bind[0].buffer_length= strlen(filename);

    bind[1].buffer_type  = MYSQL_TYPE_BLOB;
    bind[1].buffer       = buffer;
    bind[1].length       = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Could not bind parameters\n");
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Could not execute statement\n");
        exit(1);
    }

    mysql_stmt_close(stmt);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    store_image_in_db(argv[1], conn);
    printf("Image stored successfully in database.\n");

    mysql_close(conn);
    return 0;
}