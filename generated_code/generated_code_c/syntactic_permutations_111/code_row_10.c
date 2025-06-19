// Importing libraries for URL and other functionalities
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_BUFFER 1024 // To store the output of the ping command
int main(void)
{
// Function to ping an IP address or a URL
char *ping(char *url)
{
// Store the output in a variable called "output"
char output[MAX_BUFFER];
// Run the system command to execute the ping function
int status = system("ping -c 4 $url");
if (status == -1)
{
perror("Error: ");
exit(EXIT_FAILURE);
}
return output;
}