#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

// Define product prices
static const struct {
    char *code;
    double price;
} products[] = {
    {"P001", 10.99},
    {"P002", 15.49},
    {"P003", 23.89}
};

// Function to get the price for a given product code
double getProductPrice(const char *code) {
    size_t n = sizeof(products) / sizeof(products[0]);
    for (size_t i = 0; i < n; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

// Function to calculate total price based on product code and quantity
static void handle_calculate_price(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST && hm->method == MGHTTP_GET) {
        char code[256];
        char quantity_str[256];
        double quantity;
        char response[512];

        mg_get_http_var(hm, "code", code, sizeof(code));
        mg_get_http_var(hm, "quantity", quantity_str, sizeof(quantity_str));

        if (sscanf(quantity_str, "%lf", &quantity) != 1 || strlen(code) == 0) {
            snprintf(response, sizeof(response), "Invalid request");
            mg_send_head(nc, 400, strlen(response), "Content-Type: text/plain");
            mg_printf(nc, "%s", response);
        } else {
            double price = getProductPrice(code);
            if (price < 0) {
                snprintf(response, sizeof(response), "Product not found");
                mg_send_head(nc, 404, strlen(response), "Content-Type: text/plain");
                mg_printf(nc, "%s", response);
            } else {
                double total_price = price * quantity;
                snprintf(response, sizeof(response), "{\"total\": %.2f}", total_price);
                mg_send_head(nc, 200, strlen(response), "Content-Type: application/json");
                mg_printf(nc, "%s", response);
            }
        }
    }
}

// Main function
int main(void) {
    struct mg_server *server;
    struct mg_connection *nc;

    // Initialize Mongoose library
    server = mg_create_server(NULL, NULL);

    // Set up the route for calculating price
    mg_set_http_handler(server, "/calculate_price", handle_calculate_price);

    // Start listening on port 5000
    nc = mg_bind_front_end(server, "http://localhost:5000", NULL);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Enter the event loop
    printf("Starting web server on http://localhost:5000/\n");
    mg_poll_server(server, 1000);

    // Cleanup Mongoose library
    mg_destroy_server(&server);
    return 0;
}