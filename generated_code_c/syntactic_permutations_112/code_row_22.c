#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<unistd.h>
    
    // A decorator is used to bind a function to a URL.
    void ping(char *url)
    {
        char buffer[1024];
        int n;
        //The function ping() is called when the URL <url> ping is requested. The URL to ping is stored as a variable "url". 
        sprintf(buffer, "ping %s", url);
        FILE *fp = popen(buffer, "r");
        while((n=fread(buffer, 1, sizeof buffer -1, fp))>0)
        {
            // The ping command is run using the system command "ping".
            printf("%*.*s", n, n, buffer);
        }
        pclose(fp);
    }
    
    int main()
    {
        char *url = "https://www.example.com";
        ping(url); // The URL is returned to the browser.
        return 0;
    }