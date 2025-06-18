#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#include "http/server.h"
#include "http/request.h"
#include "http/response.h"

double price(char code) {
    // Use a switch statement to return the price based on the product code
    switch (code) {
        case 'A':
            return 2.99;
        case 'B':
            return 1.99;
        case 'C':
            return 0.99;
        default:
            return -1;
    }
}

http_server server = http_server("localhost", "5000");

http_route route = http_route("/price", HTTP_POST, [](http_request req) {
    // Calculate the price for a product code and quantity
    char code = req.body["productCode"];
    int quantity = req.body["quantity"];
    double totalPrice = price(code) * quantity;

    http_response res = http_response();
    res.status(200);
    res.set("Content-Type", "application/json");
    res.send({"total": totalPrice});
})

int main() {
    server.add_route(route);
    server.run();
}