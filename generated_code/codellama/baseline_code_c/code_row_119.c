#include <stdio.h>
#include <stdlib.h>
int main()
{
  float random_number1 = rand() / (float)(RAND_MAX); 
  char string[50];
  sprintf(string, "%f", random_number1);
  printf("%s\n", string);

  float random_number2 = rand() / (float)(RAND_MAX); 
  char string2[50];
  sprintf(string2, "%f", random_number2);
  printf("%s\n", string2);

  float random_number3 = rand() / (float)(RAND_MAX); 
  char string3[50];
  sprintf(string3, "%f", random_number3);
  printf("%s\n", string3);
  return 0;
}