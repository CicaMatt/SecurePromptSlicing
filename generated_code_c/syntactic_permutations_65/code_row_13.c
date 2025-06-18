#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    const char *url = "http://localhost:3000/upload";
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:";

    int main(void) {
      CURL *curl;
      CURLcode res;
      
      curl_global_init(CURL_GLOBAL_ALL);
      
      curl_formadd(&formpost,
                   &lastptr,
                   CURLFORM_COPYNAME, "pdf",
                   CURLFORM_FILE, "uploads/file.pdf",
                   CURLFORM_END);
      
      curl = curl_easy_init();
      headerlist = curl_slist_append(headerlist, buf);
      if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
  
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));
      }
    
      curl_easy_cleanup(curl);
      curl_formfree(formpost);
      curl_slist_free_all(headerlist);
      curl_global_cleanup();
      return 0;
    }