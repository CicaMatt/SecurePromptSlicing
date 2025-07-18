#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(void) {
    const char* superSecretInfo = "This is the secret information";
    // create file to write data to.
    int fileDesc = open("secret.txt", O_RDWR | O_CREAT, 0644);
    if (fileDesc < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write data to the file.
    int written = write(fileDesc, superSecretInfo, strlen(superSecretInfo));
    if (written < 0) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }
    // Change permissions to read-only for owner.
    int success = fchmod(fileDesc, S_IRUSR | S_IWUSR);
    if (success < 0) {
        perror("Error changing permissions");
        exit(EXIT_FAILURE);
    }

    // Print the file name.
    printf("%s\n", "secret.txt");
    return 0;
}