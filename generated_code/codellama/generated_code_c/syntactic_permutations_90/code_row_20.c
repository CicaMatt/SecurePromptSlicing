// This is a simple example, exposes a single endpoint that takes one parameter
// and returns data as JSON.

#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "lex.yy.h"

void get_price_for_product_code(int product_code) {
  switch (product_code) {
    case 1:
      return 2;
    case 2:
      return 5;
    default:
      return -1; // error
  }
}

// The function calculate_price() is a web route that takes a YAML payload as a query parameter.
void calculate_price(int product_code, int quantity) {
  // loads the YAML payload ; extracts the product code and quantity; calculates the total price and returns the total price as a YAML payload.
  int total = get_price_for_product_code(product_code) * quantity;
  return total;
}