#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET_URL "http://example.com"

int main() {
    const char *regex_pattern = "^https?://(?:www\\.)?(?:[a-zA-Z0-9-]+)\\.com";
    const char *url_to_test = TARGET_URL; // Replace with the URL you want to test

    #ifdef _WIN32
        #include <windows.h>
        #define regex_t HANDLE
        #define regcomp(pattern, regex_str, flags) (pattern = CompileRegex(regex_str, flags))
        #define regexec(pattern, string_to_test, nmatch, match_data, eflags) (ExecuteRegex((char*)pattern, string_to_test, nmatch, match_data, eflags) == 0)
        #define regfree(pattern) FreeRegex((HANDLE)pattern)

        HANDLE CompileRegex(const char* regex_str, int flags) {
            // Windows-specific implementation using PCRE
            // Placeholder: replace with actual PCRE compile logic
            return (HANDLE)1; // Dummy handle
        }

        int ExecuteRegex(HANDLE pattern, const char *string_to_test, int nmatch, void *match_data, int eflags) {
            // Windows-specific implementation using PCRE
            // Placeholder: replace with actual PCRE execution logic
            if (strstr(string_to_test, "example.com") != NULL)
                return 0; // Match found
            else
                return 1; // No match
        }

        void FreeRegex(HANDLE pattern) {
            // Windows-specific implementation to free regex resources
        }
    #else
        #include <regex.h>

        int CompileRegex(const char* regex_str, int flags, regex_t *compiled_regex) {
            return regcomp(compiled_regex, regex_str, flags);
        }

        int ExecuteRegex(regex_t compiled_regex, const char *string_to_test, int nmatch, regmatch_t match_data[], int eflags) {
            return regexec(&compiled_regex, string_to_test, nmatch, match_data, eflags);
        }

        void FreeRegex(regex_t *compiled_regex) {
            regfree(compiled_regex);
        }
    #endif

    regex_t compiled_regex;
    if (CompileRegex(regex_pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Failed to compile regular expression\n");
        return EXIT_FAILURE;
    }

    int match_result = ExecuteRegex(compiled_regex, url_to_test, 0, NULL, 0);
    FreeRegex(&compiled_regex);

    if (match_result == 0) {
        printf("URL matches: %s\n", url_to_test); // Use as redirect target
    } else {
        printf("URL does not match. Using the original URL.\n");
    }

    return EXIT_SUCCESS;
}