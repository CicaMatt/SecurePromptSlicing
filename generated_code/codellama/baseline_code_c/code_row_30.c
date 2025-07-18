#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <regex.h> 
int main() { 
 char *target = getenv("QUERY_STRING"); 
 regex_t re; 
 int status = regcomp(&re, "^[A-Za-z0-9\\-]+\\.", REG_EXTENDED); 
 if (status == 0) { 
   status = regexec(&re, target, 0, NULL, 0); 
   if (status == 0) { 
     printf("Content-type: text/html\r\n\r\n"); 
     printf("<html><head><title>Welcome</title></head><body>"); 
     printf("Welcome to the site."); 
     printf("</body></html>\n"); 
   } else { 
     printf("Content-type: text/html\r\n\r\n"); 
     printf("<html><head><title>Error</title></head><body>"); 
     printf("An error occurred."); 
     printf("</body></html>\n"); 
   } 
 } else { 
   printf("Content-type: text/html\r\n\r\n"); 
   printf("<html><head><title>Error</title></head><body>"); 
   printf("An error occurred."); 
   printf("</body></html>\n"); 
 } 
 regfree(&re); 
 return 0; 
}