#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "math.h"
#include "mongoose.h"  // Include Mongoose API for web server

// Defining a function to get price for an item
float getPrice(char* item) {
    float price = 0;
    
    if (strcmp(item, "Apple") == 0) {
        price = 1.50;
    } else if (strcmp(item, "Banana") == 0) {
        price = 2.25;
    } else if (strcmp(item, "Mango") == 0) {
        price = 3.75;
    } else if (strcmp(item, "Orange") == 0) {
        price = 1.80;
    } else if (strcmp(item, "Pineapple") == 0) {
        price = 6.95;
    } else {
        price = -1; // If item not found, return -1
    }
    
    return price;
}

// Defining a route to calculate the total cost of an order
void calculateTotalCost(struct mg_connection* conn, void* cbdata) {
    char buffer[BUFSIZ]; // Create a buffer for reading data from client
    int nread = 0;       // Initialize number of bytes read to zero
    
    while ((nread = mg_read(conn, buffer, sizeof(buffer))) > 0) {
        // Read the data sent by the client and save it to a string
        char* queryString = malloc((sizeof(char) * nread) + 1);
        memcpy(queryString, buffer, nread);
        queryString[nread] = '\0';
        
        char* itemName = strtok(queryString, "="); // Get the name of the fruit from the query string
        int quantity = atoi(strtok(NULL, "="));    // Get the quantity of the fruit from the query string
        
        float price = getPrice(itemName);           // Calculate the price for the fruit
        
        if (price == -1) {  // If item not found, return error message
            mg_send_status(conn, 404);
            mg_printf_http_chunk(conn, "Invalid fruit");
        } else {
            float totalCost = price * quantity; // Calculate the total cost for the order
            
            char* response = malloc((sizeof(char) * (strlen(itemName) + strlen("Total Cost: ") + 10)) + 1);
            sprintf(response, "Total Cost: %.2f", totalCost); // Create a response string
            mg_send_status(conn, 200);
            mg_printf_http_chunk(conn, response);
        }
        
        free(queryString);   // Free the query string
        free(response);      // Free the response string
    }
}

int main() {
    struct mg_context* ctx;  // Declare a Mongoose context
    
    // Define a new Mongoose configuration
    const char* options[] = {"listening_ports", "5000", NULL};
    
    // Start the web server with the defined configuration and routes
    ctx = mg_start(&calculateTotalCost, NULL, options); 
}