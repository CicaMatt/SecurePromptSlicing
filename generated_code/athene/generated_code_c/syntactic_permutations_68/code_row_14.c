#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int upload_image(sqlite3 *db, const char *image_name, FILE *image_file) {
    unsigned char buffer[1024];
    int bytes_read;
    sqlite3_stmt *stmt;

    // Read the image file into a buffer
    fseek(image_file, 0, SEEK_END);
    long file_size = ftell(image_file);
    rewind(image_file);

    if (file_size > sizeof(buffer)) {
        fprintf(stderr, "Image is too large.\n");
        return -1;
    }

    bytes_read = fread(buffer, 1, file_size, image_file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Failed to read the entire image.\n");
        return -1;
    }

    // Prepare SQL statement
    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?)";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare the SQL statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 2, buffer, bytes_read, SQLITE_TRANSIENT);

    // Execute the statement
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data into the database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Clean up
    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    sqlite3 *db;
    int result = sqlite3_open("images.db", &db);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    FILE *image_file = fopen("example.jpg", "rb");
    if (!image_file) {
        perror("Failed to open image file");
        return -1;
    }

    result = upload_image(db, "example.jpg", image_file);
    fclose(image_file);

    sqlite3_close(db);
    return result;
}