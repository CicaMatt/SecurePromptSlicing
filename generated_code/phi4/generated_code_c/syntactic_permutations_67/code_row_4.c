#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void error_exit(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        error_exit("Unable to open file.");
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for the image data
    unsigned char *data = (unsigned char *)malloc(file_size);
    if (!data) {
        error_exit("Memory allocation failed.");
    }

    // Read the image file into memory
    size_t read_bytes = fread(data, 1, file_size, file);
    if (read_bytes != (size_t)file_size) {
        free(data);
        fclose(file);
        error_exit("Error reading file.");
    }
    fclose(file);

    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned long lengths[1] = {0};
    my_bool is_nulls[1] = {0};

    conn = mysql_init(NULL);
    if (!conn) {
        error_exit("mysql_init() failed.");
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 3306, NULL, 0) == NULL) {
        error_exit(mysql_error(conn));
    }

    const char *query = "INSERT INTO images_table (image_data) VALUES (?)";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        mysql_close(conn);
        error_exit("mysql_stmt_init() failed.");
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        mysql_close(conn);
        error_exit(mysql_stmt_error(stmt));
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = data;
    bind[0].buffer_length = file_size;
    bind[0].length = &lengths[0];
    bind[0].is_null = &is_nulls[0];

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_close(conn);
        error_exit(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_close(conn);
        error_exit(mysql_stmt_error(stmt));
    }

    printf("Image uploaded successfully.\n");

    mysql_stmt_close(stmt);
    mysql_close(conn);

    free(data);

    return EXIT_SUCCESS;
}