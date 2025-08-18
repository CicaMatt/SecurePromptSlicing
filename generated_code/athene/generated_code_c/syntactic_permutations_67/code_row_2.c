#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void die_with_error(MYSQL *con, const char *msg) {
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Error: %s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    MYSQL *con = mysql_init(NULL);

    if (mysql_real_connect(con, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        die_with_error(con, "Failed to connect to database");
    }

    FILE *image_file = fopen(argv[1], "rb");
    if (!image_file) {
        die_with_error(NULL, "Failed to open image file");
    }

    fseek(image_file, 0, SEEK_END);
    long file_size = ftell(image_file);
    rewind(image_file);

    unsigned char *image_data = malloc(file_size);
    if (fread(image_data, 1, file_size, image_file) != file_size) {
        die_with_error(NULL, "Failed to read image data");
    }

    fclose(image_file);

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_hex_string(con, image_data, file_size));

    if (mysql_query(con, query)) {
        die_with_error(con, "Failed to insert image data");
    }

    free(image_data);
    mysql_close(con);

    return 0;
}