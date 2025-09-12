#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    FILE *file;
    unsigned long length;
    void *buffer;
    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; // replace with your password
    const char *database = "testdb";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        exit(1);
    }

    file = fopen(argv[1], "rb");
    if (!file) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);

    buffer = malloc(length);
    if (buffer == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    fread(buffer, 1, length, file);
    fclose(file);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        free(buffer);
        exit(1);
    }

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string_quote(conn, buffer, length));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        free(buffer);
        exit(1);
    }

    printf("Image successfully stored in the database.\n");

    mysql_close(conn);
    free(buffer);
    return 0;
}