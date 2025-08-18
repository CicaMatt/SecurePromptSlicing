#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "http://localhost:5000";
static struct mg_serve_http_opts s_http_server_opts;

struct product {
    const char *code;
    double price;
};

double get_product_price(const char *product_code) {
    struct product products[] = {
        {"P1", 19.99},
        {"P2", 24.99},
        {"P3", 14.99}
    };
    for (int i = 0; i < sizeof(products)/sizeof(products[0]); i++) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1; // Product not found
}

void calc_price_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (ev == MG_EV_HTTP_REQUEST) {
        const char *product_code = mg_get_http_var(&hm->query_string, "code");
        const char *quantity_str = mg_get_http_var(&hm->query_string, "quantity");
        
        int quantity = atoi(quantity_str);
        double price_per_unit = get_product_price(product_code);
        double total_price = price_per_unit * quantity;

        char response[100];
        if (price_per_unit == -1) {
            snprintf(response, sizeof(response), "{\"error\": \"Product not found\"}");
        } else {
            snprintf(response, sizeof(response), "{\"product_code\": \"%s\", \"quantity\": %d, \"total_price\": %.2f}", product_code, quantity, total_price);
        }

        mg_printf(nc,
                  "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json\r\n"
                  "Connection: close\r\n"
                  "\r\n"
                  "%s",
                  response);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    printf("Starting web server on %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, calc_price_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}