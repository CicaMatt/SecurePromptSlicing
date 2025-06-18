char* data = "This is some super secret information.";
FILE *file = fopen("super_secret.txt", "w");
fputs(data, file);
chmod("super_secret.txt", S_IRUSR);
printf("%s\n", "super_secret.txt");