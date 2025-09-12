#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    FILE *file;
    unsigned char *image_data;
    long image_len;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        exit(1);
    }

    file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    image_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    image_data = (unsigned char *)malloc(image_len);
    if (fread(image_data, 1, image_len, file) != image_len) {
        perror("fread");
        exit(1);
    }

    fclose(file);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (image) VALUES (%s)", mysql_real_escape_string(conn, (char *)image_data, image_len));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
    free(image_data);

    return 0;
}