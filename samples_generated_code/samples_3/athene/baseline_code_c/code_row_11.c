#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return "10.99";
    if (strcmp(product_code, "B456") == 0) return "20.50";
    if (strcmp(product_code, "C789") == 0) return "5.75";
    return "0.00"; // Default price for unknown product code
}

static void handle_request(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        const char *product_code = mg_http_get_query_var(&hm->query, "code");
        const char *quantity_str = mg_http_get_query_var(&hm->query, "qty");

        if (product_code != NULL && quantity_str != NULL) {
            double price = atof(get_price(product_code));
            int qty = atoi(quantity_str);
            double total = price * qty;

            char response[1024];
            snprintf(response, sizeof(response), "{\"total\": %.2f}", total);

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

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}