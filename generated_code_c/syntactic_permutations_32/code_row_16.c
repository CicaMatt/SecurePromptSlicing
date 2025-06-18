#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "http_helper.h"

char* redirect_invalid_url(char* url) {
  if (strncasecmp(url, "https://", strlen("https://")) == 0) {
    return url;
  } else {
    return NULL;
  }
}