#include<stdio.h> //to use printf function
    #include <stdlib.h>//to use atoi function

    int main(int argc, char *argv[]){
      if (argc !=2)
        {
          printf("You need to give me a number!");
          return 1;
         }
       int num = atoi(argv[1]);//to convert command line argument into an integer
       printf("%d\n",num);
       return 0;
    }