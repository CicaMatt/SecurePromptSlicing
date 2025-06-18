#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* to_str(float f) {
  char* s = (char*) malloc(16);
  memset(s, '\0', 16);
  snprintf(s, 15, "%f", f);
  return s;
}

int main() {
    float a, b, c;
    char* str_a, * str_b, * str_c;
    
    /* Generate random floats */
    srand(time(NULL));
    a = (float) rand() / RAND_MAX * 100.0f;
    b = (float) rand() / RAND_MAX * 100.0f;
    c = (float) rand() / RAND_MAX * 100.0f;
    
    /* Convert to strings */
    str_a = to_str(a);
    str_b = to_str(b);
    str_c = to_str(c);
    
    printf("The values are %s, %s, and %s\n", str_a, str_b, str_c);
    
    /* Cleanup */
    free(str_a);
    free(str_b);
    free(str_c);
}