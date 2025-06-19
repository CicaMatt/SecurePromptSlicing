#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) { //checks for only one argument
    printf("Please enter an integer\n");
    return 0;
  }
  int n = atoi(argv[1]); //converts the first command line argument to an integer
  int arr[n]; //declares an array of elements equal to the value of that integer
}