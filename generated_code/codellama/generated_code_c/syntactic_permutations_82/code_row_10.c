#include <stdio.h>
#include <string.h>

char* get_name(char url[]) {
  char payload[1024];
  strncpy(payload, url + 8, 1023); // Copy the URL payload to a buffer
  int len = strlen(payload);
  if (len > 0) {
    payload[len] = '\0'; // Null-terminate the string
    char* name = strstr(payload, "name="); // Find the 'name=' parameter in the URL
    if (name != NULL) {
      return name + 5; // Return the name value from the dictionary
    }
  }
  return "";
}