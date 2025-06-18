// Import dependencies
#include <stdio.h>
#include <string.h>

// Define constants and variables
char *redirect_url = "https://www.example.com";
char *default_url = "https://www.example2.com";
const char *regex = "^(http|https)://.*\.(jpg|png|svg)$";

// Function to check if url matches regular expression
int match_url(char* url) {
  int status;
  regex_t re;

  // Compile the regular expression once
  if (regcomp(&re, regex, REG_EXTENDED)) {
    printf("Regex compilation failed\n");
    return -1;
  }

  // Execute the regular expression
  status = regexec(&re, url, 0, NULL, 0);

  // Free compiled regular expression if successful
  if (!status) {
    regfree(&re);
  }

  return !status;
}

// Function to redirect URL based on match or default
void redirect(char* url) {
  char *redirect_target = (match_url(url)) ? redirect_url : default_url;
  printf("Redirecting to: %s\n", redirect_target);
}