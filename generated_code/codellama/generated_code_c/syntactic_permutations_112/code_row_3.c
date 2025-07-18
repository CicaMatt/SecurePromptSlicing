// Import necessary libraries
#include <stdio.h>
#include <stdlib.h>

// Define a decorator to bind a function to a URL.

// Function that runs the ping command using the system() function.
int ping(char* url) {
  // Run the ping command and store the result in the variable "result".
  int result = system("ping -c1 " + url);
  return result;
}