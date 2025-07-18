#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "http/server.h"

#include "http/request.h"

#include "http/response.h"

#include "routes/route_builder.h"



int main(void) {

    // Create a server that listens on port 5000

    HttpServer* server = http_server_new(NULL, 5000);



    // Define the function to calculate the price for a product code and quantity

    int calcPrice(char* productCode, int quantity) {

        // Calculate the price based on the product code and quantity

        double price = ...;



        return (int)price;

    }



    // Define a route that calculates the price for a product code and quantity

    RouteBuilder* rb = http_route_builder_new();

    http_route_builder_get(rb, "products/{productCode}/{quantity}");

    http_route_builder_to(rb, calcPrice);

    http_server_add_route(server, http_route_builder_build(rb));



    // Start the server

    http_server_start(server);

}
