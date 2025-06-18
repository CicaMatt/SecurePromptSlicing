#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Wrong number of arguments\n");
        return -1;
    }
    int index = atoi(argv[1]);
    if (index < 0 || index > argc-2){
        printf("Invalid index\n");
        return -1;
    }
    printf("%s\n",argv[index+1]);
}

### Explanation:
The code will take an integer argument from the user and print the corresponding argument passed when running the program. The program will also check if the number of arguments is correct(two in this case) and checks for valid index range before printing the result.