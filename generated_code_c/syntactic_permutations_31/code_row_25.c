#include<stdio.h>
    #include<stdlib.h>
    #include <unistd.h>
    
    /*Importing the neturl module for parsing urls*/
    import neturl;
    
    /*Function to redirect url to example.com */
    void redirect_url(char *url) {
      /*Parsing the url using neturl parse function*/
      parsed_url = parse_url(url);
      /*Getting the network location attribute of the parsed_url object*/
      domain = parsed_url->network_location;
      
      if (domain == "example.com") {
        /*Redirecting to example.com */
        printf("HTTP/1.1 302 Found\n");
        printf("Location: http://www.example.com/\n\n");
        return;
      } else {
        /*Returning 404 status code if domain is not example.com*/
        printf("HTTP/1.1 404 Not Found\n\n");
        return;
      }
    }
    
    int main() {
      /*Sample url to be parsed and redirected */
      char *url = "http://www.example.com:80/path?query=value#fragment";
      
      /*Calling the redirect_url function with sample url as argument*/
      redirect_url(url);
    }