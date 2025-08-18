#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 65536

void save_image_to_db(const char *filename, const char *db_host, const char *db_user, const char *db_password, const char *db_name) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    unsigned long filesize = 0;
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(filesize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, filesize, file);
    fclose(file);

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, db_user, db_password, db_name, 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        free(buffer);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES ('%s')",
             mysql_real_escape_string(conn, buffer, filesize));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
    } else {
        printf("Image saved to database successfully.\n");
    }

    mysql_close(conn);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <image_file> <db_host> <db_user> <db_password> <db_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    save_image_to_db(argv[1], argv[2], argv[3], argv[4], argv[5]);

    return EXIT_SUCCESS;
}