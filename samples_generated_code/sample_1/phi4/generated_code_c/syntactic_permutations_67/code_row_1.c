#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void connect_mysql(MYSQL **conn);
void store_image_in_db(MYSQL *conn, const char *file_path);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    MYSQL *conn = NULL;
    connect_mysql(&conn);

    store_image_in_db(conn, argv[1]);

    mysql_close(conn);
    return EXIT_SUCCESS;
}

void connect_mysql(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (*conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(*conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        exit(EXIT_FAILURE);
    }
}

void store_image_in_db(MYSQL *conn, const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", file_path);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    const char *query = "INSERT INTO images (image_data) VALUES (?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        free(buffer);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        free(buffer);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    my_bool is_null = 0;
    my_bool error = 0;

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = (char *)buffer;
    bind[0].buffer_length = file_size;
    bind[0].is_null = &is_null;
    bind[0].error = &error;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        free(buffer);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        free(buffer);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    mysql_stmt_close(stmt);
    free(buffer);

    printf("Image stored successfully.\n");
}