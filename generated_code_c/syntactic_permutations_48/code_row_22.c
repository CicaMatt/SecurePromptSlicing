#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

void img(request, response){
    char *file = request->args->get('file');
    
    int fd = open(file, O_RDONLY);
    
    if (fd == -1) {
        return response->send("File not found", 404);
    }
    
    struct stat st;
    fstat(fd, &st);
    
    char *data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    
    response->send(data, 200);
}