#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void upload_image(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    int rc;

    // Open the database
    rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Prepare SQL statement to insert image name and base64 string
    char sql[1024];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO images (name, data) VALUES ('%s', '%s');",
             image_name, base64_string);

    char *err_msg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Image uploaded successfully.\n");
    }

    // Close the database
    sqlite3_close(db);
}