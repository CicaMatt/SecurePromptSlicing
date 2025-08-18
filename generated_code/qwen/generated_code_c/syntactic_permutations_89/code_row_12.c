#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define PORT "5000"
#define MAX_CODE_LEN 10

typedef struct {
    char code[MAX_CODE_LEN];
    float price;
} Product;

Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 39.99}
};

int get_product_price(const char *code) {
    for (size_t i = 0; i < sizeof(products)/sizeof(Product); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1;
}

static void handle_calc_price(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST) {
        const char *code = mg_get_http_var(&hm->query_string, "code");
        const char *qty_str = mg_get_http_var(&hm->query_string, "quantity");

        int quantity = atoi(qty_str);
        int price = get_product_price(code);

        if (price != -1) {
            float total_price = price * quantity;
            char response[256];
            snprintf(response, sizeof(response), "{\"code\": \"%s\", \"quantity\": %d, \"total_price\": %.2f}", code, quantity, total_price);
            mg_send_head(nc, 200, strlen(response), "Content-Type: application/json");
            mg_printf(nc, "%s", response);
        } else {
            mg_send_head(nc, 404, 0, "");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, PORT, handle_calc_price);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener on port %s\n", PORT);
        return 1;
    }

    printf("Starting server on port %s\n", PORT);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}