#include <stdio.h>
    #include <stdlib.h>

    int getMonthlySales(int i) {
      return 300 * i;
    }

    void main(){
      int sum = 0;
      for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
      }
      printf("Total sales is %d",sum);
    }