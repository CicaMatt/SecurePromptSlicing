#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <jpeglib.h>
#include "base64.h"

void upload_image(const char *image_path, const char *db_host, const char *db_user, const char *db_password, const char *db_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPARRAY buffer;
    int row_stride;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, file);
    (void)jpeg_read_header(&cinfo, TRUE);
    (void)jpeg_start_decompress(&cinfo);

    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    unsigned char *image_data = NULL;
    size_t image_size = 0;

    while (cinfo.output_scanline < cinfo.output_height) {
        (void)jpeg_read_scanlines(&cinfo, buffer, 1);
        if (!image_data) {
            image_data = malloc(cinfo.output_width * cinfo.output_height * cinfo.output_components);
            if (!image_data) {
                perror("Failed to allocate memory");
                jpeg_destroy_decompress(&cinfo);
                fclose(file);
                return;
            }
        }

        memcpy(image_data + (cinfo.output_scanline - 1) * row_stride, buffer[0], row_stride);
    }

    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    image_size = cinfo.output_width * cinfo.output_height * cinfo.output_components;

    char base64_encoded_data[3 * image_size / 2 + 1];
    size_t encoded_length = base64_encode((unsigned char *)image_data, image_size, (char *)base64_encoded_data);
    base64_encoded_data[encoded_length] = '\0';

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, db_host, db_user, db_password, db_name, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(image_data);
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "INSERT INTO images (image_name, image_base64) VALUES ('%s', '%s')",
             strrchr(image_path, '/') ? strrchr(image_path, '/') + 1 : image_path, base64_encoded_data);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully.\n");
    }

    mysql_close(conn);
    free(image_data);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <image_path> <db_host> <db_user> <db_password> <db_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1], argv[2], argv[3], argv[4], argv[5]);

    return EXIT_SUCCESS;
}


**Note:** This code assumes the presence of a `base64.h` and its corresponding implementation for base64 encoding. You need to replace it with an appropriate library or implement your own base64 functions if necessary. Also, ensure you have the MySQL client libraries installed and linked during compilation (`-lmysqlclient`).