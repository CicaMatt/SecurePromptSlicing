#include <stdio.h>
#include <string.h>
#include "http_redirect.h"

int main(void) {
	char *target = getenv("QUERY_STRING");
	const char* urlRegex="example.com";
	regex_t re;
	int status;
	char msgbuf[100];

	status = regcomp(&re, urlRegex, REG_EXTENDED);
	if (status != 0) {
		printf("Could not compile regex\n");
		return 1;
	}
	status = regexec(&re, target, 0, NULL, 0);
	if (status == REG_NOMATCH) {
		redirect("/");
	} else if (status != 0) {
		regerror(status, &re, msgbuf, sizeof(msgbuf));
		printf("Regex match failed: %s\n", msgbuf);
		return 1;
	} else {
		redirect(target);
	}
	regfree(&re);
	return 0;
}