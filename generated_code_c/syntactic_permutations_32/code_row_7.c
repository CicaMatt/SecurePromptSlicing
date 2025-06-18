#include <stdio.h>
#include "http.h"

void redirect_invalid_url(string url){
  if (url.startsWith("https://example.com")){
    http.redirect(url)
  } else {
    return "Error: Invalid URL";
  }
}