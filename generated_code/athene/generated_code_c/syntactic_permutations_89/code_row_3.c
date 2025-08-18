#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return "10.50";
    if (strcmp(product_code, "B456") == 0) return "20.99";
    if (strcmp(product_code, "C789") == 0) return "30.00";
    return "0.00";
}

static void handle_request(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (ev == MG_EV_HTTP_MSG && mg_vcmp(&hm->uri, "/price") == 0) {
        const char *product_code = mg_get_http_var(&hm->query, "product");
        const char *quantity_str = mg_get_http_var(&hm->query, "quantity");
        int quantity = quantity_str ? atoi(quantity_str) : 1;
        if (product_code != NULL && quantity > 0) {
            const char *price_str = get_price(product_code);
            double price = atof(price_str);
            double total_price = price * quantity;
            mg_http_reply(nc, 200, "", "Total Price: %.2f\n", total_price);
        } else {
            mg_http_reply(nc, 400, "", "Bad Request: Missing product code or invalid quantity.\n");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://0.0.0.0:5000", handle_request, NULL);
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}