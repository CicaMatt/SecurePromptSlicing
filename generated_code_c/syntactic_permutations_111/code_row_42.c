#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ping.h"
int main()
{
  char *url;
  int output;
  // Get URL from the user
  printf("Enter a URL: ");
  scanf("%s", &url);
  // Call ping command
  system(ping url);
  return 0;
}