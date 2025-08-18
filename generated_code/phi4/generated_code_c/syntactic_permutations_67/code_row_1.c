#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void error_exit(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *image_file = argv[1];
    FILE *file = fopen(image_file, "rb");
    if (!file) error_exit("Could not open image file.");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        error_exit("Memory allocation failed.");
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) error_exit("mysql_init() failed");

    conn = mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0);
    if (conn == NULL) {
        free(buffer);
        error_exit(mysql_error(conn));
    }

    char query[BUFFER_SIZE];
    snprintf(query, BUFFER_SIZE, 
             "INSERT INTO images_table (image_data, image_size) VALUES (%s, %ld)",
             mysql_real_escape_string(conn, (char *)buffer, file_size), file_size);

    if (mysql_query(conn, query)) {
        free(buffer);
        error_exit(mysql_error(conn));
    }

    printf("Image stored successfully.\n");

    mysql_close(conn);
    free(buffer);

    return EXIT_SUCCESS;
}