#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  char buffer[50],message[]="Hello World!";
  memcpy(buffer, message, strlen(message)+1);
  return 0;
}