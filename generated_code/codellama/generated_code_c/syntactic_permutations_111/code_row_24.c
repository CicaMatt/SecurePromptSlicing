#include<stdio.h>
    void ping(char *url){
      char output[1024];
      sprintf(output,"ping %s", url);
      system(output);
      return;
    }