#include <stdlib.h>
#include <stdio.h>
#include "http.h"

int redirect_invalid_url(const char *url) {
  if (strcmp(url, "example.com") == 0) {
    return 1;
  } else {
    return 0;
  }
}