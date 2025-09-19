#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <base64.h>

void upload_image(const char *image_path, const char *db_path) {
    FILE *file = fopen(image_path, "rb");
    if (file == NULL) {
        perror("Failed to open image file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fsize + 1);
    if (buffer == NULL) {
        fclose(file);
        perror("Failed to allocate memory");
        return;
    }

    fread(buffer, fsize, 1, file);
    fclose(file);
    buffer[fsize] = '\0';

    size_t out_len;
    char *encoded_data = base64_encode(buffer, fsize, &out_len);
    free(buffer);

    if (encoded_data == NULL) {
        fprintf(stderr, "Failed to encode image data\n");
        return;
    }

    sqlite3 *db;
    int rc = sqlite3_open(db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(encoded_data);
        return;
    }

    char sql[1024];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", image_path, encoded_data);

    char *zErrMsg = NULL;
    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Image uploaded successfully.\n");
    }

    free(encoded_data);
    sqlite3_close(db);
}