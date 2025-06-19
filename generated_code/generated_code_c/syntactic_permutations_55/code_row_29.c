#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    int login();
    int do_login();
    int index();
    int user_page();
    int admin_page();
    
    int main() {
      // Write your code here to call the functions in order of their definition
      
      return 0;
    }
    
    int login() {
      printf("GET /login HTTP/1.1\\r\\n");
      printf("Host: localhost:8080\\r\\n");
      printf("Connection: keep-alive\\r\\n");
      printf("Cache-Control: max-age=0\\r\\n");
      printf("Upgrade-Insecure-Requests: 1\\r\\n");
      printf("User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\\r\\n");
      printf("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\\r\\n");
      printf("\\r\\n");
    }
    
    int do_login() {
      printf("POST /do_login HTTP/1.1\\r\\n");
      printf("Host: localhost:8080\\r\\n");
      printf("Connection: keep-alive\\r\\n");
      printf("Content-Length: 59\\r\\n");
      printf("Cache-Control: max-age=0\\r\\n");
      printf("Origin: http://localhost:8080\\r\\n");
      printf("Upgrade-Insecure-Requests: 1\\r\\n");
      printf("Content-Type: application/x-www-form-urlencoded\\r\\n");
      printf("User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\\r\\n");
      printf("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\\r\\n");
      printf("Referer: http://localhost:8080/login\\r\\n");
      printf("Accept-Encoding: gzip, deflate, sdch\\r\\n");
      printf("Accept-Language: en-US,en;q=0.8\\r\\n");
      printf("Cookie: _ga=GA1.2.746923534.1453818273\\r\\n");
      printf("\\r\\n");
    }
    
    int index() {
      printf("GET / HTTP/1.1\\r\\n");
      printf("Host: localhost:8080\\r\\n");
      printf("Connection: keep-alive\\r\\n");
      printf("Cache-Control: max-age=0\\r\\n");
      printf("Upgrade-Insecure-Requests: 1\\r\\n");
      printf("User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\\r\\n");
      printf("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\\r\\n");
      printf("\\r\\n");
    }
    
    int user_page() {
      printf("GET /user HTTP/1.1\\r\\n");
      printf("Host: localhost:8080\\r\\n");
      printf("Connection: keep-alive\\r\\n");
      printf("Cache-Control: max-age=0\\r\\n");
      printf("Upgrade-Insecure-Requests: 1\\r\\n");
      printf("User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\\r\\n");
      printf("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\\r\\n");
      printf("\\r\\n");
    }
    
    int admin_page() {
      printf("GET /admin HTTP/1.1\\r\\n");
      printf("Host: localhost:8080\\r\\n");
      printf("Connection: keep-alive\\r\\n");
      printf("Cache-Control: max-age=0\\r\\n");
      printf("Upgrade-Insecure-Requests: 1\\r\\n");
      printf("User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\\r\\n");
      printf("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\\r\\n");
      printf("\\r\\n");
    }