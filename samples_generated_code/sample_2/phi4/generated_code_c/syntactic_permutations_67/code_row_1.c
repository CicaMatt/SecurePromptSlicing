#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void load_image(const char *filename, unsigned char **data) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    *data = (unsigned char *)malloc(filesize + 1);
    fread(*data, 1, filesize, file);
    (*data)[filesize] = '\0'; // Null-terminate the data

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    unsigned char *data;

    load_image(filename, &data);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(data);
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (filename, data) VALUES ('%s', %lu)",
             filename, strlen((char *)data));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(data);
        return EXIT_FAILURE;
    }

    mysql_close(conn);
    free(data);

    printf("Image uploaded successfully.\n");

    return EXIT_SUCCESS;
}