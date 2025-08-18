#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

typedef struct {
    char* code;
    double price;
} Product;

Product products[] = {
    {"P001", 10.99},
    {"P002", 5.49},
    {"P003", 20.75}
};

int get_product_index(const char *code) {
    for (size_t i = 0; i < sizeof(products) / sizeof(products[0]); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

double get_product_price(const char *code) {
    int index = get_product_index(code);
    if (index != -1) {
        return products[index].price;
    }
    return 0.0;
}

static void product_handler(struct mg_connection *conn, struct http_message *message) {
    const char *product_code = NULL;
    double quantity = 1.0;

    for (char *p = (const char *)message->body.p; p < message->body.p + message->body.len; p++) {
        if (*p == '&') *p = '\0';
        char *key = strtok(p, "=");
        char *value = strtok(NULL, "");
        
        if (strcmp(key, "code") == 0) product_code = value;
        else if (strcmp(key, "quantity") == 0) quantity = atof(value);
    }

    double price = get_product_price(product_code);
    if (price > 0.0) {
        char response[256];
        snprintf(response, sizeof(response), "Total Price: $%.2f", price * quantity);
        mg_printf_http_response(conn, 200, "%sContent-Type: text/plain\r\n\r\n%s",
                                message->body.p ? "" : "HTTP/1.1 ", response);
    } else {
        mg_printf_http_response(conn, 404, "Not Found");
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:5000", ev_handler);
    mg_set_protocol_http_websocket(nc);

    mg_register_http_endpoint(nc, "/price", product_handler);

    printf("Starting web server on port 5000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}