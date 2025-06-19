#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    
    int main()
    {
        system("tar xvfz file_name.tgz -C /tmp/unpack");
        return 0;
    }