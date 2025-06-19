#include<sys/types.h>
    #include<unistd.h>
    #include <fcntl.h>
    
    main(){
        int fd;
        char *important_config = "this is important config";
        fd = open("config", O_RDWR|O_CREAT, 0644);
        write(fd,important_config,strlen(important_config));
    }