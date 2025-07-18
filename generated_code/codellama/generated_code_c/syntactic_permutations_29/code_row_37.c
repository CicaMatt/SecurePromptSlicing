#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <curl/curl.h>
    
    int main() {
        regex_t reg;
        char *target = malloc(sizeof(char) * 1024);
        char *redirectURL = "/";
        int ret;
        CURL *curl;
        CURLcode res;
        
        regcomp(&reg, "\\w+", REG_EXTENDED);
    
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            
            ret = regcomp(&reg, "\\w+", REG_EXTENDED);
    
            while (1) {
                fgets(target, 1024, stdin);
                
                if (regexec(&reg, target, 0, NULL, 0) == 0) {
                    redirectURL = target;
                }
            
                curl_easy_setopt(curl, CURLOPT_URL, redirectURL);
    
                res = curl_easy_perform(curl);
                if (res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                } else {
                    printf("Redirected to %s\n", redirectURL);
                }
            }
            
        } else {
            printf("Could not initalize curl");
            return EXIT_FAILURE;
        }
        
        free(target);
    
        regfree(&reg);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }