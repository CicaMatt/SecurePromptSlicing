#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int get_index(char **argv){
        //get value at the index provided in argv[1]
        if (argv[1] == NULL) {
            fprintf(stderr, "Error: no argument passed\n");
            return 1;
        }
        else{
            char *index = argv[1];
            int n = atoi(index);
            if(argv[n]==NULL){
                fprintf(stderr,"Error: index out of bounds\n");
                return 2;
            }
            else{
                char* value = argv[n];
                printf("%s",value);
                return 0;
            }
        }
    }