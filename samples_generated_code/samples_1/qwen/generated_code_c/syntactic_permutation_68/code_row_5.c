#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "images.db"

void die(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void upload_image(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        die("Cannot open database");
    }

    char *sql = "INSERT INTO images (name, base64) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        die("Failed to prepare statement");
    }

    rc = sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        die("Failed to bind image name");
    }

    rc = sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        die("Failed to bind base64 string");
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        die("Execute statement failed");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_string = "/9j/4AAQSkZJRgABAQEAYABgAAD/2wBDAAUDBAQEAwUEBAQFBQUGBwwIBwcHBw8LCwkMEQ8SEhEPERETFhwXExQaFRERGCEYGh0dHx8fGCIyHiIjJSkrLi4uFx8zODMtNygtLisBCgoKDg0OGxAQGy0lICYtLS0tLSstLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLf/AABEIAKgBLAMBIgACEQEDEQH/xAAbAAACAwEBAQAAAAAAAAAAAAAFBgADBAUHAf/EAEIQAAIBAgMFBAYHBQcDAAAAAAECAwAEEQUSITEGEyJBUWFxgZGhscHR8BRCUrLR4fDxUnKCkuHx8RU0YjNkNTVEobLS/8QAFQEBAAMAAAAAAAAAAAAAAAAAAAEC/8QAFTABAAIBAQEBAAAAAAAAAAAAAAECEgMRITESUv/aAAwDAQACEQMRAD8A+ZV6n//2Q==";

    upload_image(image_name, base64_string);

    return 0;
}