#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <jpeglib.h>  // For JPEG handling
#include "base64.h"   // Assuming you have a base64 library

// Function prototypes
void upload_image(const char *image_path, sqlite3 *db);
int convert_jpeg_to_base64(const char *input_filename, char **output_base64);
int insert_into_database(sqlite3 *db, const char *image_name, const char *base64_str);

void upload_image(const char *image_path, sqlite3 *db) {
    FILE *file = fopen(image_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return;
    }

    // Extract image name from path
    char *image_name = strdup(basename(image_path));
    
    char *base64_str = NULL;
    int result = convert_jpeg_to_base64(image_path, &base64_str);
    if (result != 0) {
        fprintf(stderr, "Failed to convert image to base64\n");
        free(image_name);
        fclose(file);
        return;
    }

    // Insert into database
    insert_into_database(db, image_name, base64_str);

    free(base64_str);
    free(image_name);
    fclose(file);
}

int convert_jpeg_to_base64(const char *input_filename, char **output_base64) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *infile = fopen(input_filename, "rb");
    if (!infile) {
        fprintf(stderr, "Unable to open %s\n", input_filename);
        return -1;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void)jpeg_read_header(&cinfo, TRUE);
    (void)jpeg_start_decompress(&cinfo);

    // Calculate output size
    unsigned long size = 0;
    JSAMPROW row_pointer[1];
    while (cinfo.output_scanline < cinfo.output_height) {
        row_pointer[0] = (JSAMPROW)malloc(cinfo.output_width * cinfo.output_components);
        if (!row_pointer[0]) {
            fprintf(stderr, "Memory error\n");
            return -1;
        }
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
        size += cinfo.output_width * cinfo.output_components;
        free(row_pointer[0]);
    }
    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    // Allocate buffer for JPEG data
    unsigned char *buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "Memory error\n");
        return -1;
    }

    infile = fopen(input_filename, "rb");
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void)jpeg_read_header(&cinfo, TRUE);
    (void)jpeg_start_decompress(&cinfo);

    unsigned long offset = 0;
    JSAMPROW row_pointer[1];
    while (cinfo.output_scanline < cinfo.output_height) {
        row_pointer[0] = (JSAMPROW)malloc(cinfo.output_width * cinfo.output_components);
        if (!row_pointer[0]) {
            fprintf(stderr, "Memory error\n");
            return -1;
        }
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
        memcpy(buffer + offset, row_pointer[0], cinfo.output_width * cinfo.output_components);
        offset += cinfo.output_width * cinfo.output_components;
        free(row_pointer[0]);
    }

    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    // Convert to base64
    size_t encoded_size = base64_encode_expected(buffer, size);
    *output_base64 = malloc(encoded_size + 1);
    if (!*output_base64) {
        fprintf(stderr, "Memory error\n");
        free(buffer);
        return -1;
    }
    base64_encode(*output_base64, buffer, size);

    free(buffer);
    return 0;
}

int insert_into_database(sqlite3 *db, const char *image_name, const char *base64_str) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement\n");
        return -1;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_str, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    const char *db_path = ":memory:";
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "CREATE TABLE images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Example usage
    upload_image("example.jpg", db);

    sqlite3_close(db);
    return 0;
}