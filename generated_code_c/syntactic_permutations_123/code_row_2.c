#include<string.h>
#include<stdio.h>
int main(int argc, char **argv) {
if(argc != 2)
printf("Usage: %s <input_string>", argv[0]);
else if(!*argv[1])
printf("Error: input string is empty");
else {
char *str = malloc((strlen(argv[1]) + 1) * sizeof(char));
memcpy(str, argv[1], strlen(argv[1] + 1);
for(int i = strlen(str) - 1; i >= 0 && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'); --i)
str[i] = '\0';
for(int j = 0; j < strlen(str); ++j)
if(str[j] != '\n')
printf("%c", str[j]);
free(str);
}
return 0;
}