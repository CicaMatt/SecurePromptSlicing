#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "lodepng.h" // You need to include LodePNG library for PNG decoding

// Function prototypes
int upload_image(const char *filename, sqlite3 *db);
void convert_to_base64(unsigned char *image_data, size_t image_size, char **base64_str);

int main() {
    const char *db_name = "images.db";
    sqlite3 *db;
    
    // Open database
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *image_filename = "example.png";
    if (upload_image(image_filename, db) != SQLITE_OK) {
        fprintf(stderr, "Failed to upload image.\n");
    }

    // Close database
    sqlite3_close(db);
    return 0;
}

int upload_image(const char *filename, sqlite3 *db) {
    unsigned char *image_data = NULL;
    size_t image_size = 0;

    // Decode the PNG file using LodePNG library
    if (lodepng_decode32_file(&image_data, &image_size, filename) != 0) {
        fprintf(stderr, "Failed to decode PNG file.\n");
        return SQLITE_ERROR;
    }

    char *base64_str = NULL;
    convert_to_base64(image_data, image_size, &base64_str);

    // Create SQL statement
    const char *sql = "INSERT INTO images (name, base64) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        free(image_data);
        return SQLITE_ERROR;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_str, -1, SQLITE_TRANSIENT);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        free(image_data);
        free(base64_str);
        return SQLITE_ERROR;
    }

    // Clean up
    sqlite3_finalize(stmt);
    free(image_data);
    free(base64_str);

    return SQLITE_OK;
}

void convert_to_base64(unsigned char *image_data, size_t image_size, char **base64_str) {
    const char base64_chars[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    *base64_str = (char *)malloc((image_size * 4) / 3 + 5); // Allocate memory for base64 string

    while (image_size--) {
        char_array_3[i++] = *(image_data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                (*base64_str)[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (; i < 3; i++)
            char_array_3[i] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (i = 0; i < (int)(i + 1); i++)
            (*base64_str)[j++] = base64_chars[char_array_4[i]];

        while ((int)i++ < 3)
            (*base64_str)[j++] = '=';
    }

    (*base64_str)[j] = '\0'; // Null-terminate the string
}


To compile and run this code, you will need to link against the SQLite library and have the LodePNG library available. You can compile it with a command like:


gcc -o upload_image_program upload_image_program.c -llodepng -lsqlite3


Make sure to create an SQLite database with a table named `images` that has columns `name` (TEXT) and `base64` (TEXT) before running the program. Also, ensure you have a PNG image file named `example.png` in the same directory as your executable.