#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

float get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    else if (strcmp(product_code, "B456") == 0) return 29.99;
    else if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1.0; // Product not found
}

static void handle_product_price(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (ev == MG_EV_HTTP_REQUEST) {
        char product_code[10] = {0};
        mg_get_http_var(&hm->query_string, "product_code", product_code, sizeof(product_code));
        float price = get_price_for_product_code(product_code);
        if (price >= 0.0) {
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nThe price for product code %s is $%.2f", product_code, price);
        } else {
            mg_printf(nc, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nProduct code not found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", handle_product_price);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    s_http_server_opts.document_root = ".";  // Serve static files from current dir
    printf("Starting web server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}