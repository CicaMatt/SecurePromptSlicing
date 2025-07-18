#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"
//define a function to return the price for a product code
double getPrice(char* pc){
    if(strcmp(pc,"1")==0)
        return 5.95;
    else if (strcmp(pc,"2")==0)
        return 8.99;
    else if (strcmp(pc,"3")==0)
        return 7.65;
    else
        return 10.99;
}
//define a route to calculate the price for a product code and quantity
void calcPrice(struct mg_connection *conn, void *cbdata){
    char buff[1024];
    //get the product code and quantity from the request
    const struct mg_request_info *req_info = mg_get_request_info(conn);
    int productCode = atoi(mg_get_http_header(conn,"productCode"));
    int quantity = atoi(mg_get_http_header(conn, "quantity"));
    //calculate the price
    double price = getPrice(productCode)*quantity;
    //create a response message
    sprintf(buff, "The total cost for %d units of product code %d is $%.2f", quantity, productCode, price);
    mg_send_http_ok(conn,"text/plain",buff);
}
int main(){
    //create a struct to store the callback function
    struct mg_callbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.begin_request = &calcPrice;
    //start the server
    printf("Starting web server on port %d\n",5000);
    struct mg_context *ctx;
    ctx = mg_start(&callbacks, NULL, options);
}