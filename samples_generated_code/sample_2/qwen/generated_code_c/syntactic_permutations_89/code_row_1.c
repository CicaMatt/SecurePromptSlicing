#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "http://localhost:5000";
static struct mg_serve_http_opts s_http_server_opts;

double get_price_for_product(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    else if (strcmp(product_code, "B456") == 0) return 19.99;
    else if (strcmp(product_code, "C789") == 0) return 29.99;
    return -1.0; // Product not found
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (ev == MG_EV_HTTP_REQUEST) {
        const char* uri = hm->uri.p;
        if (strncmp(uri, "/calculate_price?", 17) == 0) {
            char product_code[10] = {0};
            int quantity = 0;
            mg_get_http_var(&hm->query_string, "product_code", product_code, sizeof(product_code));
            mg_get_http_var2(&hm->query_string, "quantity", (long *) &quantity);
            double price_per_unit = get_price_for_product(product_code);
            if (price_per_unit == -1.0) {
                mg_printf(nc, "%s", "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
            } else {
                double total_price = price_per_unit * quantity;
                char response[50];
                snprintf(response, sizeof(response), "{\"total_price\": %.2f}", total_price);
                mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s", (int)strlen(response), response);
            }
        } else {
            mg_serve_http(nc, hm, s_http_server_opts); // Serve static files
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    printf("Starting web server on %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}