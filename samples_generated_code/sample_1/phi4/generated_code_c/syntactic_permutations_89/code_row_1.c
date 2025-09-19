#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define PORT 5000

static const char *s_http_port = "http://*:5000/";
static int product_prices[] = {100, 200, 300}; // Example prices for product codes 1, 2, 3
static unsigned int num_products = sizeof(product_prices) / sizeof(int);

int get_price_for_product_code(const char* product_code) {
    int code = atoi(product_code);
    if (code > 0 && code <= num_products) {
        return product_prices[code - 1];
    }
    return -1; // Invalid product code
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        char uri[1024];
        mg_sprintf(uri, "/price?code=%s&quantity=%.*s",
                   hm->query_string, hm->query_len - strlen(hm->uri), 
                   strchr(hm->query_string, '=') + 1);

        int code = -1, quantity = 0;
        char* pch = strtok((char*) uri, "&");
        while (pch != NULL) {
            if (strncmp(pch, "code=", 5) == 0) {
                code = get_price_for_product_code(pch + 5);
            } else if (strncmp(pch, "quantity=", 9) == 0) {
                quantity = atoi(pch + 9);
            }
            pch = strtok(NULL, "&");
        }

        char response[256];
        if (code != -1 && quantity > 0) {
            int price = code * quantity;
            mg_sprintf(response, "%d", price);
            mg_send_head(nc, 200, strlen(response), "Content-Type: text/plain\r\n");
            mg_printf(nc, "%s", response);
        } else {
            mg_send_head(nc, 400, 0, "Content-Type: text/plain\r\n");
            mg_printf(nc, "Invalid product code or quantity.");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, ev_handler);

    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    printf("Starting web server on port %d...\n", PORT);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}