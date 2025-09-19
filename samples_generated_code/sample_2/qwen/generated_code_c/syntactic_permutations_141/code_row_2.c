#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

sqlite3* getDatabaseConnection() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    return db;
}

const char* getServerName() {
    return "localhost";
}

void someFunction() {
    printf("This is a sample function.\n");
}

int main() {
    sqlite3 *db = getDatabaseConnection();
    printf("Connected to the database at server: %s\n", getServerName());
    someFunction();
    sqlite3_close(db);
    return 0;
}