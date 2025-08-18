#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    FILE *file;
    unsigned char *blob;
    long blob_len;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        exit(1);
    }

    file = fopen(argv[1], "rb");
    if (!file) {
        perror("File opening failed");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    blob_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    blob = (unsigned char *)malloc(blob_len + 1);
    if (!blob) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return 1;
    }

    fread(blob, 1, blob_len, file);
    fclose(file);

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(blob);
        mysql_close(conn);
        return 1;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO images (image) VALUES (%s)", mysql_real_escape_string_quote(conn, blob, blob_len));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(blob);
        mysql_close(conn);
        return 1;
    }

    free(blob);
    mysql_close(conn);

    printf("Image stored in database successfully.\n");
    return 0;
}