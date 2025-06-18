#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(void) {
  const char *pattern = "http://example\\.com/.*";
  regex_t regex;
  int reti;

  if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    perror("Error compiling regular expression");
    return EXIT_FAILURE;
  }

  const char *url = "http://example.com/path/?q=string";
  reti = regexec(&regex, url, 0, NULL, 0);
  if (reti == REG_NOMATCH) {
    printf("No match\n");
  } else {
    printf("Match\n");
  }

  regfree(&regex);
}