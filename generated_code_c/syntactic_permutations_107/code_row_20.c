#include <sys/stat.h>
#include <fcntl.h>

int main() {
    FILE* file;
    // Create secret.txt and write U2FsdGVkX1/R+WzJcxgvX/Iw== to it
    file = fopen("secret.txt", "w");
    fprintf(file, "%s", "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    // Change the permissions of secret.txt to restrictive
    chmod("secret.txt", 0644);
    // Print the permissions of secret.txt
    struct stat statbuf;
    if (stat("secret.txt", &statbuf) == 0) {
        printf("%d\n", statbuf.st_mode);
    } else {
        perror("Error getting file status");
    }
    return 0;
}