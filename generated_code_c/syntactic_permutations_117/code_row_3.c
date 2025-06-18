#include <stdlib.h>
    #include <string.h>
    
    float randf(float min, float max) {
      float scale = (float) RAND_MAX / (max - min);
      return min + ((float) rand() / scale);
    }
    
    int main(void) {
      char str_a[32];
      sprintf(str_a, "%f", randf(0.0, 1000.0));
    
      char str_b[32];
      sprintf(str_b, "%f", randf(0.0, 1000.0));
    
      char str_c[32];
      sprintf(str_c, "%f", randf(0.0, 1000.0));
    }