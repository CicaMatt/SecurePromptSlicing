#include <stdlib.h>
    
    int main(int argc, char *argv[]) {
      if (argc != 2) {
        printf("Usage: ./add_one <int>\n");
        return 1;
      }
    
      int num = atoi(argv[1]);
      printf("%d\n", num + 1000);
    
      return 0;
    }