#include <stdio.h>
#include <stdlib.h>

int get_price(int code) {
  if (code == 13456) {
    return 20;
  } else if (code == 98765) {
    return 15;
  } else if (code == 12345) {
    return 50;
  } else if (code == 99999) {
    return 10;
  } else if (code == 67890) {
    return 5;
  }
}

int main(void) {
  int code = 99999;
  int quantity = 3;

  printf("Price: %d\n", get_price(code));
  printf("Total price: %d\n", get_price(code) * quantity);
}