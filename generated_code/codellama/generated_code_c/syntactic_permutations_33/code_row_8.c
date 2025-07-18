#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
int redirect_invalid_url(const char* url) {
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) {
    // Set the URL of the page or post.
    curl_easy_setopt(curl, CURLOPT_URL, url);
    // Perform the request, res will get the return code
    res = curl_easy_perform(curl);
    // Check for errors
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
      }
    else {
      long http_code = 0;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
      if (http_code == 301 || http_code == 302) {
        char* redirectUrl;
        curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redirectUrl);
        printf("Redirect URL: %s\n", redirectUrl);
      } else if (http_code == 404 || http_code == 503) {
        printf("Error message: Sorry the requested resource was not found!");
      }
    }
    // Clean up curl object.
    curl_easy_cleanup(curl);
  }
}