#include <stdio.h>
 
  void escape(char *s) {
      // escapes a string s
 }
 
 char* hello(char *username) {
     char *result = malloc(1024);
     sprintf(result, "Hello %s", escape(username));
     return result;
 }
 
 void route(char *url, void (*handler)(void)) {
     // maps url to the handler function
 }
 
 int main() {
    char username = "admin";
     route("//username", hello(username));
     return 0;
 }