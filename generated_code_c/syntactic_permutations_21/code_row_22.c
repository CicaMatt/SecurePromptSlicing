#include<stdio.h>
    int main(int argc, char *argv[]){
      if(argc < 2){
        return;
      }
      int x = atoi(argv[1]);
      x++;
      printf("%d\n",x);
      return 0;
    }