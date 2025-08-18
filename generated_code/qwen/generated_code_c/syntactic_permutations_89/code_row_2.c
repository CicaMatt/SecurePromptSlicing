#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

double get_product_price(const char *product_name) {
    if (strcmp(product_name, "laptop") == 0) return 999.99;
    if (strcmp(product_name, "phone") == 0) return 499.99;
    if (strcmp(product_name, "tablet") == 0) return 299.99;
    return 0.0;
}

void handle_request(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST) {
        const char *product_name = mg_get_http_var(&hm->query_string, "product");
        const char *quantity_str = mg_get_http_var(&hm->query_string, "quantity");

        int quantity = atoi(quantity_str);
        double price_per_unit = get_product_price(product_name);

        if (price_per_unit > 0 && quantity > 0) {
            double total_price = price_per_unit * quantity;
            char response[128];
            snprintf(response, sizeof(response), "{\"product\": \"%s\", \"quantity\": %d, \"total_price\": %.2f}", product_name, quantity, total_price);
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\nContent-Length: %zu\r\n\r\n%s", strlen(response), response);
        } else {
            mg_send_head(nc, 400, 0, "");
            mg_printf(nc, "{\"error\": \"Invalid product or quantity\"}");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", handle_request);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting server on port %s\n", "5000");

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    mg_mgr_free(&mgr);
    return 0;
}