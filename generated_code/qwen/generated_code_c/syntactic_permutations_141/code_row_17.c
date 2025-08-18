#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming SQLite is used as the database and TinyCgi for web app framework

#include "sqlite3.h"
#include "tinycgi.h"

sqlite3 *getDatabaseConnection() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    return db;
}

const char* getServerName() {
    return "MyWebAppServer";
}

void handleRequest(tiny_cgi *cgi) {
    tiny_cgi_put(cgi, "<html><body>");
    tiny_cgi_printf(cgi, "<h1>Welcome to %s</h1>", getServerName());
    
    sqlite3 *db = getDatabaseConnection();
    char *err_message = 0;
    const char *sql = "SELECT 'Hello from the database!'";
    
    int rc = sqlite3_exec(db, sql, callback, (void*)cgi, &err_message);
    if (rc != SQLITE_OK) {
        tiny_cgi_printf(cgi, "<p>SQL error: %s</p>", err_message);
        sqlite3_free(err_message);
    }
    
    sqlite3_close(db);
    tiny_cgi_put(cgi, "</body></html>");
}

int callback(void *data, int argc, char **argv, char **azColName) {
    tiny_cgi *cgi = (tiny_cgi*) data;
    for(int i=0; i<argc; i++) {
        tiny_cgi_printf(cgi, "<p>%s: %s</p>", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int main() {
    tiny_cgi cgi;
    tiny_cgi_init(&cgi);
    handleRequest(&cgi);
    tiny_cgi_free(&cgi);
    return 0;
}