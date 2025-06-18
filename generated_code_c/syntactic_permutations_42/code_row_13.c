// Importing libraries required for this code to run.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

// Defining a global struct that contains the username, email and ssn of the user.
struct userInfo {
  char *username;
  char *email;
  int ssn;
};

// A function to get all user info from session and return it as string.
char* info() {
	struct userInfo user;
	user.username = "John Doe";
	user.email = "johndoe@example.com";
	user.ssn = 1234567890;

	char *info = malloc(sizeof(char) * 50);
	sprintf(info, "%s\t%s\t%d", user.username, user.email, user.ssn);

	return info;
}

// A function to route the request.
void router() {
	char* res = info();
	printf("%s", res);
	free(res);
}

// The main entry point of the program.
int main() {
  // Initialize all necessary libraries.
  curl_global_init(CURL_GLOBAL_DEFAULT);
  struct Curl_easy *curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    curl_easy_perform(curl);
  }
  curl_global_cleanup();

  // Call the router function.
  router();
  return 0;
}