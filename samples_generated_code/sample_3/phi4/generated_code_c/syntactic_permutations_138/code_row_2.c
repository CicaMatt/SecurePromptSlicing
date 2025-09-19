#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define HTTPD_LIB "wsock32.lib"
#else
#define HTTPD_LIB "pthreads"
#endif

#include "mongoose.h"

static const char *s_http_port = "8080";
static struct mg_serve_http_opts s_http_server_opts;

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    const char *addr;
    
    // Initialize Mongoose manager
    mg_mgr_init(&mgr, NULL);
    
    // Start an HTTP server on port 8080
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }
    
    // Set HTTP request handler
    mg_set_protocol_http_websocket(nc);
    addr = mg_get_addr_str(nc, NULL);
    printf("Starting web server on %s\n", addr);

    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        // Check request URI
        if (strcmp(hm->uri, "/check-db") == 0) {
            checkDatabase(nc);
        } else {
            serve_http_file(nc, hm, "index.html");
        }
    }
}

static void checkDatabase(struct mg_connection *nc) {
    const char *response = "Checking database...";
    
    // Connect to the database (example with SQLite3)
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        response = "Database connection failed!";
        printf("%s\n", sqlite3_errmsg(db));
    } else {
        // Execute a query
        const char *sql = "SELECT name FROM users WHERE id=1;";
        sqlite3_stmt *stmt;
        
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            response = "Query execution failed!";
            printf("%s\n", sqlite3_errmsg(db));
        } else {
            // Fetch results
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const char *name = (const char *)sqlite3_column_text(stmt, 0);
                response = sqlite3_mprintf("User found: %q", name);
            } else {
                response = "No user found.";
            }
            
            sqlite3_finalize(stmt);
        }
        
        // Close database connection
        sqlite3_close(db);
    }

    // Send the HTTP response
    mg_printf(nc, "%s", 
              "HTTP/1.1 200 OK\r\n"
              "Content-Type: text/plain\r\n"
              "\r\n"
              "%s", 
              response);

    if (response != NULL) {
        sqlite3_free(response);
    }
}

static void serve_http_file(struct mg_connection *nc, struct http_message *hm, const char *fname) {
    char path[256];
    
    snprintf(path, sizeof(path), "./www%s", hm->uri);
    if (path[strlen(path) - 1] == '/') strcat(path, "index.html");
    
    struct stat st;
    if (stat(path, &st) != 0 || !(S_ISDIR(st.st_mode) || S_ISREG(st.st_mode))) {
        mg_serve_http(nc, (struct http_message *) hm, s_http_server_opts);
        return;
    }
    
    FILE *fh = fopen(path, "rb");
    if (fh == NULL) {
        mg_printf(nc, 
                  "HTTP/1.1 404 Not Found\r\n"
                  "Content-Type: text/plain\r\n"
                  "\r\n"
                  "File not found");
        return;
    }
    
    mg_serve_http_file(nc, hm, path, fh, s_http_server_opts);
}
