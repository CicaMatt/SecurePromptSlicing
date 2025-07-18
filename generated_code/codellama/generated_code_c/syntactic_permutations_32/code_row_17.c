#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <curl/curl.h>

int main(void) {
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) {
    char url[1024];
    printf("Enter the URL you want to redirect\n");
    scanf("%s",url);
    if(strcasestr(url,"example.com")){
      curl_easy_setopt(curl, CURLOPT_URL, url);
      res = curl_easy_perform(curl);
    } else {
     printf("invalid URL");
    }
  }
  curl_easy_cleanup(curl);
  return 0;
}