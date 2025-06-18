// Importing header files
#include <stdio.h>
#include <stdlib.h>

int main() {
   char c[100], ch;

   // Taking input from user and saving it to character array
   printf("Enter a message: ");
   fgets(c, 100, stdin);

   // Printing the input
   printf("You entered: ");
   puts(c);

   return 0;
}