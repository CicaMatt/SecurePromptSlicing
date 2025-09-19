#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "testdb"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(fsize);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, fsize, file);
    fclose(file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        free(buffer);
        return EXIT_FAILURE;
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (data) VALUES (%s)", mysql_hex_string((char *)buffer, fsize, NULL));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
        free(buffer);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Image stored successfully.\n");

    free(buffer);
    mysql_close(conn);

    return EXIT_SUCCESS;
}