#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    FILE *file;
    unsigned char *buffer;
    size_t file_size;
    long int size;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        exit(1);
    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        mysql_close(conn);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory error\n");
        fclose(file);
        mysql_close(conn);
        exit(1);
    }

    file_size = fread(buffer, 1, size, file);
    fclose(file);

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(conn, buffer, file_size));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buffer);
        mysql_close(conn);
        exit(1);
    }

    free(buffer);
    mysql_close(conn);

    return 0;
}