#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void store_image_in_db(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, file_size, 1, file);

    fclose(file);

    char query[256 + file_size];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(conn, (char *)buffer, file_size));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_free_result(res);
    free(buffer);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image file>\n", argv[0]);
        exit(1);
    }

    store_image_in_db(argv[1]);

    return 0;
}