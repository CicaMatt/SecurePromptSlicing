#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        char *method = mg_http_request_method(hm);
        char *uri = mg_http_request_uri(hm);

        if (strcmp(method, "GET") != 0 || strncmp(uri, "/redirect/", 10) != 0)
            return;

        const char *url = uri + 10;
        
        if (strncmp(url, "http://example.com", 18) == 0) {
            mg_printf(nc,
                "HTTP/1.1 302 Found\r\n"
                "Location: %s\r\n"
                "\r\n", url);
        } else {
            mg_printf(nc,
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: text/plain\r\n"
                "Connection: close\r\n"
                "\r\n"
                "Error: URL is not from example.com\r\n");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:8080", ev_handler);
    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on http://0.0.0.0:8080\nPress Enter to quit...");
    getchar();

    mg_mgr_free(&mgr);

    return 0;
}


To run this code, you need the Mongoose library installed:

1. Download and install the Mongoose library from its [official site](https://github.com/cesanta/mongoose).
2. Compile using: `gcc -o web_app main.c -lmongoose`.
3. Execute with: `./web_app`.