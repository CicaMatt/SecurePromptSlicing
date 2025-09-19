#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define BUFFER_SIZE 1048576 // 1 MB buffer size for reading the image

void handle_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    mysql_close(conn);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_file> <db_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    const char *db_name = argv[2];

    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        handle_error(conn, "mysql_init() failed");
    }

    conn = mysql_real_connect(conn, "localhost", "root", "", db_name, 3306, NULL, 0);
    if (conn == NULL) {
        handle_error(conn, mysql_error(conn));
    }

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return EXIT_FAILURE;
    }

    long file_size = 0;
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    buffer[file_size] = '\0';

    const char query_template[] =
        "INSERT INTO images (file_name, image_data) VALUES (%s, %s)";

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        handle_error(conn, "mysql_stmt_init() failed");
    }

    const char *query = mysql_real_escape_string(conn, buffer + file_size + 1,
                                                 query_template, strlen(query_template));
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        handle_error(conn, mysql_stmt_error(stmt));
    }

    MYSQL_BIND bind[2] = {0};

    const char *file_name = strrchr(file_path, '/');
    file_name = file_name ? file_name + 1 : file_path;

    my_bool is_null = 0;
    MYSQL_TIME file_time;

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)file_name;
    bind[0].buffer_length = strlen(file_name);
    bind[0].is_null = &is_null;
    bind[0].length = 0;

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = buffer;
    bind[1].buffer_length = file_size;
    bind[1].is_null = &is_null;
    bind[1].length = &file_size;

    if (mysql_stmt_bind_param(stmt, bind)) {
        handle_error(conn, mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt)) {
        handle_error(conn, mysql_stmt_error(stmt));
    }

    free(buffer);
    mysql_stmt_close(stmt);
    mysql_close(conn);

    printf("Image successfully stored in database.\n");

    return EXIT_SUCCESS;
}