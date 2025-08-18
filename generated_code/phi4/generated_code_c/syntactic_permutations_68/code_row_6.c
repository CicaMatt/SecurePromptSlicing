#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <jpeglib.h>
#include "base64.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "image_db"

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    char base64_string[3 * file_size / 2 + 1];
    if (!encode_base64((char *)buffer, file_size, base64_string)) {
        fprintf(stderr, "Base64 encoding failed\n");
        free(buffer);
        return;
    }
    base64_string[3 * file_size / 2] = '\0';

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME,
                            0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buffer);
        mysql_close(conn);
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             filename, base64_string);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    free(buffer);
    mysql_close(conn);
}

int main() {
    const char *filename = "image.jpg";
    upload_image(filename);
    return 0;
}


Make sure you have the `base64.c` and `base64.h` files in your project directory as they are required for base64 encoding. These can be obtained from common C libraries or implemented separately based on your needs.

Additionally, ensure that:
- MySQL is installed and running.
- The database `image_db` exists with a table named `images` having columns `image_name` (VARCHAR) and `image_data` (TEXT).
- You have the necessary permissions to connect and modify the database.