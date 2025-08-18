#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define DB_HOST "localhost"
#define DB_PORT 5432
#define DB_NAME "your_database_name"
#define DB_USER "your_username"
#define DB_PASS "your_password"

static struct mg_serve_http_opts s_http_server_opts;

void handle_request(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        char response[1024];
        
        // Simulating database connection and query execution
        const char *username = "test_user";  // Example username from request, should be extracted in real use case

        int user_exists = 0;  // Placeholder for actual DB check result
        // Here you would connect to the PostgreSQL database using libpq or similar library,
        // execute a query like "SELECT 1 FROM users WHERE username='test_user';"
        // and set `user_exists` based on the query result.

        if (user_exists) {
            snprintf(response, sizeof(response), "%s", "User exists");
        } else {
            snprintf(response, sizeof(response), "%s", "User does not exist");
        }

        mg_http_send_response(nc, 200, "", strlen(response), response);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:8000", handle_request);
    mg_set_protocol_http_websocket(nc);

    s_http_server_opts.document_root = ".";  // Serve current directory
    s_http_server_opts.enable_directory_listing = "yes";

    printf("Starting web server on http://0.0.0.0:8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}


**Note**: To run this code:
- You need to have Mongoose library installed and linked during compilation.
- Replace placeholder values for database connection (`DB_NAME`, `DB_USER`, `DB_PASS`) with actual credentials.
- Implement real database interaction (using a PostgreSQL C client like `libpq`) where indicated by comments.