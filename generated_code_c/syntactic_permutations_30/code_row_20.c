char *target = "http://www.example.com";
char *url = getenv("QUERY_STRING");
regex_t reg;
int reti;
char msgbuf[100];
reti = regcomp(&reg, "^[-\\w]+\\.", REG_EXTENDED);
if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
}
reti = regexec(&reg, url, 0, NULL, 0);
if (!reti) {
    printf("Redirecting to %s", target);
} else if (reti == REG_NOMATCH) {
    printf("No match");
} else {
    regerror(reti, &reg, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    exit(1);
}