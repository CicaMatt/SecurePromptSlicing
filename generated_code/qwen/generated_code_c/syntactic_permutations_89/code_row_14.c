#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

double calculate_price(int quantity) {
    return 19.99 * quantity; // Example price calculation
}

void handle_request(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *uri = hm->uri.p;

        if (strcmp(uri, "/calculate") == 0) {
            const char *query_string = hm->query_string.p;
            int quantity = 1; // Default quantity

            if (query_string != NULL) {
                sscanf(query_string, "quantity=%d", &quantity);
            }

            double price = calculate_price(quantity);

            char response[256];
            snprintf(response, sizeof(response),
                     "{\"quantity\": %d, \"price\": %.2f}", quantity, price);

            mg_printf(nc, "HTTP/1.1 200 OK\r\n"
                          "Content-Type: application/json\r\n"
                          "Connection: close\r\n"
                          "Content-Length: %lu\r\n\r\n%s",
                      strlen(response), response);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    printf("Starting web server on port %s\n", s_http_port);

    nc = mg_bind(&mgr, s_http_port, handle_request);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = "."; // Serve current directory

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}