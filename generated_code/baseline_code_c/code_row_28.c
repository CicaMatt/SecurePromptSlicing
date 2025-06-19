#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define MAX_URL_LEN 1024 
void set_redirect(const char *url) { printf("Redirecting to %s", url); } void redirect() { const char *default_url = "https://example.com"; const char *target_url = getenv("REDIRECT_URL"); if (NULL == target_url) { set_redirect(default_url); return; }
char regex[MAX_URL_LEN] = "^https?://www\\.example\\.(com|net)/.*$"; const char *pattern = strstr(target_url, "REGEX:"); if (NULL != pattern) { memcpy(regex, pattern + 6, strlen(pattern)); }
const regex_t *compiled_regex = NULL; compiled_regex = malloc(sizeof(regex_t)); int err = regcomp(compiled_regex, regex, REG_EXTENDED); if (0 != err) { perror("Could not compile regular expression."); exit(1); }
if (0 == regexec(compiled_regex, target_url, 0, NULL, 0)) set_redirect(target_url); else set_redirect(default_url); return; } int main() { redirect(); return 0; }