#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "lodepng.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "image_db"

unsigned char* read_image_to_base64(const char *filename, size_t *out_len) {
    unsigned char image_data[8192];
    unsigned char *base64 = NULL;
    size_t image_size;

    FILE *file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    image_size = fread(image_data, 1, sizeof(image_data), file);
    fclose(file);

    if (image_size > 0 && lodepng_encode_memory(&base64, out_len, image_data, image_size, LCT_RGB, 8)) {
        free(base64);
        return NULL;
    }

    return base64;
}

void upload_image(const char *filename) {
    size_t base64_len;
    unsigned char *base64 = read_image_to_base64(filename, &base64_len);

    if (!base64) {
        fprintf(stderr, "Error reading image\n");
        return;
    }

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(base64);
        mysql_close(conn);
        return;
    }

    const char *insert_query = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)";
    char query[256 + base64_len];
    snprintf(query, sizeof(query), insert_query, filename, base64);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    free(base64);
    mysql_close(conn);
}

int main() {
    const char *image_filename = "example.png";
    upload_image(image_filename);
    return 0;
}


**Note**: Before running this code, ensure you have the following:
1. MySQL database and table set up with a schema like `CREATE TABLE images (id INT AUTO_INCREMENT PRIMARY KEY, image_name VARCHAR(255), image_data TEXT);`.
2. LodePNG library compiled and linked during building of your program.
3. Appropriate MySQL client libraries installed on your system (`libmysqlclient-dev` for example).