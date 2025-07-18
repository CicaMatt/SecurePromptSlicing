#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef void (*function)(void);

static void ping(char *url) {
  char cmd[1024];
  snprintf(cmd, sizeof(cmd), "ping %s", url); // BAD: unsanitized user input passed to shell command
  system(cmd);
}

static void bind_url(function f, char *url) {
  f(url);
}

int main() {
  char *url = "www.example.com";
  bind_url(&ping, url); // BAD: unsanitized user input passed to shell command
  return 0;
}