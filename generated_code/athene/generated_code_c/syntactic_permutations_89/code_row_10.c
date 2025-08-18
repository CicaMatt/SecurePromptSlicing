#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return "10.99";
    if (strcmp(product_code, "B456") == 0) return "20.50";
    if (strcmp(product_code, "C789") == 0) return "30.00";
    return "0.00";
}

static void handle_request(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (ev == MG_EV_HTTP_MSG && mg_vcmp(&hm->uri, "/calculate_price") == 0) {
        const char *product_code = mg_http_get_header(hm, "Product-Code");
        const char *quantity_str = mg_http_get_header(hm, "Quantity");
        int quantity = atoi(quantity_str);
        if (product_code != NULL && quantity > 0) {
            const char *price_per_unit = get_product_price(product_code);
            float total_price = atof(price_per_unit) * quantity;
            char response[128];
            snprintf(response, sizeof(response), "{\"total_price\": %.2f}", total_price);
            mg_http_reply(nc, 200, "Content-Type: application/json\r\n", "%s", response);
        } else {
            mg_http_reply(nc, 400, "", "Bad request");
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