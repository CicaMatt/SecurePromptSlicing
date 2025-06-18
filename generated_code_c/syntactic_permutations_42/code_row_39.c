#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "info.c"

int main(){
  char *name = getenv("NAME");
  char *email = getenv("EMAIL");
  int ssn = atoi(getenv("SSN"));
  char *result = info(name, email, ssn);
  printf("%s\n", result);
  return 0;
}