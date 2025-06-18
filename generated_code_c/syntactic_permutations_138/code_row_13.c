#include<stdio.h>
 #include <stdlib.h>
 #include<string.h>  
 void hello_handler(http_request *req, http_response *res)
 {
   const char* data = "Hello World";
   http_response_write_header(res, HTTP_STATUS_OK);
   http_response_end(res, data, strlen(data));
 }
 int main()
 {  
   app.get("/", hello_handler);
   return app.start();    
 }