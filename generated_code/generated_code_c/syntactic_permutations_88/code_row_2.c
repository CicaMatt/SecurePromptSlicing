// YAML Parser
typedef struct yaml_t {
   char* name;
   double price;
} yaml_t;

static yaml_t* parse_yaml(const char* payload) {
   // Implement a simple YAML parser here.
}

// calculate_price function
#include <stdio.h>
#include <stdlib.h>
#include "yaml_parser.h"

char* calculate_price(const char* payload, int quantity) {
   yaml_t* product = parse_yaml(payload);
   double total_price = product->price * quantity;
   // Convert the total price to a string and return it.
}