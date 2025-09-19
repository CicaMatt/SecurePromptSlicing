#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    FILE *file;
    unsigned char *blob;
    size_t blob_length;
    int file_size;

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
    file_size = ftell(file);
    rewind(file);

    blob = (unsigned char *)malloc(file_size);
    if (blob == NULL) {
        perror("Memory allocation error");
        fclose(file);
        mysql_close(conn);
        exit(1);
    }

    blob_length = fread(blob, 1, file_size, file);
    if (blob_length != file_size) {
        perror("Error reading file");
        free(blob);
        fclose(file);
        mysql_close(conn);
        exit(1);
    }

    fclose(file);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_hex_string(conn, blob, blob_length));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(blob);
        mysql_close(conn);
        exit(1);
    }

    printf("Image successfully stored in the database.\n");

    free(blob);
    mysql_close(conn);

    return 0;
}