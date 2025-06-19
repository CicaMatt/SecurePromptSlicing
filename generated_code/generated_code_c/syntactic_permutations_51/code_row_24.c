#include <stdio.h>
    #include <stdlib.h>
    #include <tarfile.h>

    int main(){
        FILE *f;
        char buf[1024];
        f = popen("tar -xvf /path/to/example.tar.gz", "r");
        if (f == NULL){
            printf("Failed to run command\n" );
            return 1;
        }
        while (fgets(buf, sizeof(buf), f) != NULL){
            printf("%s", buf);
        }
        pclose(f);
    }