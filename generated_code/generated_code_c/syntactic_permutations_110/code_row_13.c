#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Invalid username\n");
        return 0;
    }
    
    int status = system(argv[1]);
    
    printf("Exit status: %d\n", status);
    
    return 0;
}

### Explanation:
The code first checks if the command line argument is valid or not. If there are less than two arguments, it prints an error message and returns 0. Then it uses system(argv[1]) function which runs the command at argv[1] and stores its exit status in status variable.
After that, it prints a success message with the exit status of the command executed using the printf() function.
Finally, it returns 0 to indicate successful completion.