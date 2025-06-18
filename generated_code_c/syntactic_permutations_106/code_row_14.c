char *some_secret_info = "I love pizza";
FILE* fp;
fp = fopen("some_file", "w");
fputs(some_secret_info, fp);
fclose(fp);
system("chmod 400 some_file");
printf("%s\n", "some_file");