#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = malloc(length);
    if (fread(data, 1, length, file) != length) {
        perror("Error reading file");
        fclose(file);
        mysql_close(conn);
        free(data);
        return EXIT_FAILURE;
    }

    fclose(file);

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (data) VALUES (%s)", mysql_real_escape_string_quote(conn, data, length));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        free(data);
        return EXIT_FAILURE;
    }

    printf("Image stored in database successfully.\n");

    mysql_close(conn);
    free(data);

    return EXIT_SUCCESS;
}