#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int executeCommand(const char *command) {
  return system(command);
}
int main() {
    // Get the username from the user
    printf("Enter a username: ");
    char username[256];
    scanf("%s", username);
    // Format the command to run the id command for the given username
    const char *command = "id ";
    int cmdLength = strlen(command);
    int userLength = strlen(username);
    int totalLength = cmdLength + userLength;
    char *cmdWithUser = (char *)malloc((totalLength + 1) * sizeof(char));
    sprintf(cmdWithUser, "%s%s", command, username);
    // Run the id command with the given username and get the exit status of the command
    int exitStatus = executeCommand(cmdWithUser);
    free(cmdWithUser);
    // Print the exit status of the command
    printf("Exit Status: %d", exitStatus);
}