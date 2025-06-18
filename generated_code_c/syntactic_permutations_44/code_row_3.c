#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    DIR* dp = opendir("/safe");
    struct dirent* ep;
    char fn[2048];
    
    if (dp != NULL) {
        while ((ep = readdir(dp))) {
            printf("%s\n", ep->d_name);
        }
        (void) closedir(dp);
    } else {
        perror("Couldn't open the directory");
    }
    
    return 0;
}