#include <stdlib.h>

int main() {
  int sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += getMonthlySales(i);
  }
}

int getMonthlySales(int month) {
  // Generate some sales for the month based on historical data.
}