#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void handle_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    MYSQL *con = mysql_init(NULL);

    if (mysql_real_connect(con, "localhost", "user", "password", "testdb", 0, NULL, 0) == NULL) {
        handle_error(con);
    }

    FILE *image_file = fopen(argv[1], "rb");
    if (!image_file) {
        perror("File opening failed");
        mysql_close(con);
        return 1;
    }

    fseek(image_file, 0, SEEK_END);
    long file_size = ftell(image_file);
    rewind(image_file);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, image_file);
    fclose(image_file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    stmt = mysql_stmt_init(con);
    if (mysql_stmt_prepare(stmt, "INSERT INTO images (data) VALUES (?)", -1)) {
        handle_error(con);
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].length = &file_size;

    if (mysql_stmt_bind_param(stmt, bind)) {
        handle_error(con);
    }

    if (mysql_stmt_execute(stmt)) {
        handle_error(con);
    }

    mysql_stmt_close(stmt);
    free(buffer);
    mysql_close(con);

    return 0;
}