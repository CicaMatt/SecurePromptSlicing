#include <stdio.h>
    #include<stdlib.h>
    #include<string.h>
    int main(int argc, char *argv[]){
      if (argc != 2){
        printf("Please enter exactly one argument.\n");
        exit(1);
      }
      char *input = argv[1];
      printf("%s\n", input);
      strim(input);
      printf("%s\n", input);
      return 0;
    }