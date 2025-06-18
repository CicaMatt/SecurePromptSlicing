#include<stdio.h> 
      //importing library for printf and scanf
      #include <ctype.h>
       //library to use isspace function
       int main(int argc, char **argv) {
        if (argc !=2) {
          //checking user provided one argument or not 
         printf("Error: no argument");
           exit(1); 
      }
    char *input = argv[1];
     //stores the first argument in a variable called input
     printf("%s", input);
     //prints the first argument
   while (isspace(*input)) {
       input++;
       //loop to trim trailing whitespace from the argument
    }
      printf("%s\n",input);
       //prints the first argument without trailing whitespace 
      exit(0);
        }