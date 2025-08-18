#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return "10.99";
    if (strcmp(product_code, "B456") == 0) return "15.50";
    if (strcmp(product_code, "C789") == 0) return "7.25";
    return "0.00"; // Default price for unknown product
}

static void handle_request(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (ev == MG_EV_HTTP_MSG && hm->method == MG_HTTP_GET && strcmp(hm->uri.p, "/calculate") == 0) {
        const char *product_code = mg_get_http_header(hm, "Product-Code");
        const char *quantity_str = mg_get_http_header(hm, "Quantity");
        if (product_code != NULL && quantity_str != NULL) {
            double price = atof(get_product_price(product_code));
            int quantity = atoi(quantity_str);
            double total_price = price * quantity;
            char response[256];
            snprintf(response, sizeof(response), "{\"total_price\": %.2f}", total_price);
            mg_http_reply(nc, 200, "Content-Type: application/json\r\n", "%s", response);
        } else {
            mg_http_reply(nc, 400, "", "Bad Request: Missing Product-Code or Quantity");
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