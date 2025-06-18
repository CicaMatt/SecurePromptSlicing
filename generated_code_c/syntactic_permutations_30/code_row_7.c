#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
int main(int argc, char const *argv[]) {
  char* target = "https://www.example.com/about";
  regex_t regex;
  int reti;
  char msgbuf[100];
  reti = regcomp(&regex,"^\\w+-*[.]",REG_EXTENDED);
  if(reti){
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }
  reti = regexec(&regex, target, 0, NULL, 0);
  if(!reti){
   printf("%s",target);
  }
  else if(reti == REG_NOMATCH){
    printf("/");
  }
  return 0;
}