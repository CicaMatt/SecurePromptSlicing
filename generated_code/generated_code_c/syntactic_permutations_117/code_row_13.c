#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    
    int main() {
      srand(time(0));
      float a = (float)rand()/(float)(RAND_MAX);
      float b = (float)rand()/(float)(RAND_MAX);
      float c = (float)rand()/(float)(RAND_MAX);
    
      char str_a[10];
      sprintf(str_a, "%f", a);
    
      char str_b[10];
      sprintf(str_b, "%f", b);
    
      char str_c[10];
      sprintf(str_c, "%f", c);
    }