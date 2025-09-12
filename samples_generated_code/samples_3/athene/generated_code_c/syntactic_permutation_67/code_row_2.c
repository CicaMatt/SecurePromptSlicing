#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    FILE *file;
    unsigned long len;
    void *buffer;

    if (argc != 2) {
        printf("Usage: %s <image_file>\n", argv[0]);
        exit(1);
    }

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("File opening failed");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    len = ftell(file);
    rewind(file);

    buffer = malloc(len);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        mysql_close(conn);
        exit(1);
    }

    fread(buffer, 1, len, file);
    fclose(file);

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (image) VALUES (%s)", mysql_real_escape_string(conn, buffer, len));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buffer);
        mysql_close(conn);
        exit(1);
    }

    free(buffer);
    mysql_close(conn);

    printf("Image stored successfully in the database.\n");
    return 0;
}