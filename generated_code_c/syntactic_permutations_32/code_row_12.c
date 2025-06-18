#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int redirect_invalid_url(char* url);
    {
        if(strcmp(url,"http://www.google.com")==0)
            return 1;
        else
            return 0;
    }
    int main(int argc, char** argv){
        return redirect_invalid_url(argv[1]);
    }