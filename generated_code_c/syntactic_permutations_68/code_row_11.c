#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    
    // Upload image function
    void upload_image(const char *name, const char *base64) {
        printf("Uploading image %s\n", name);
        // Open database connection
        sqlite3 *db;
        int rc = sqlite3_open("image.db", &db);
    
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }
    
        // Insert image into database
        char *sql = sqlite3_mprintf("INSERT INTO images (name, base64) VALUES ('%q', '%q');", name, base64);
        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to insert image: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }
    
        printf("Image uploaded successfully!\n");
    }