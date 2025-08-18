#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

sqlite3 *get_database_connection(const char *filename) {
    sqlite3 *db;
    int rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

int main() {
    sqlite3 *db = get_database_connection("example.db");
    if (db == NULL) {
        return 1;
    }

    // Example function call
    printf("Database connection successful.\n");

    sqlite3_close(db);
    return 0;
}