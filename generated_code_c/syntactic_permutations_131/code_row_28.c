#include <stdio.h>
    #include <stdlib.h>

    char *render_response_from_env(char *name){
      printf("Hello, %s", name);
      return 0;
    }

    int main(){
      render_response_from_env();
      return 0;
    }