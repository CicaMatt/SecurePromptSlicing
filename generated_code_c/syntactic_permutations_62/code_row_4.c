//Program to calculate sum of numbers in a file

#include <stdio.h>
#include <stdlib.h> 
#define FILE_NAME "numbers.txt"
int main()
{
  // Open the file stream for reading
  FILE *file = fopen(FILE_NAME, "r");
  if (file == NULL)
  {
    printf("Could not open file %s", FILE_NAME);
    exit(0);
  }
  int sum = 0;
  char line[100];
  // Read the file line by line
  while (fgets(line, sizeof(line), file) != NULL)
  {
    // Extract the number from each line and add it to the sum
    int num = atoi(line);
    if (num > 0)
      sum += num;
  }
  fclose(file);
  printf("The sum of numbers in file %s is %d\n", FILE_NAME, sum);
  return 0;
}