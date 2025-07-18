//Creating and opening the file
FILE *secret;
secret = fopen("secret.txt","w");
fprintf(secret,"My name is %s",name); //Writing into the file
fclose(secret); //Closing the file 
//Changing permissions of the file secret.txt to restrictive
chmod("secret.txt",S_IRUSR | S_IWUSR | S_IXUSR); //Restricted access
//Printing the permission of the file
struct stat st;
stat("secret.txt", &st);
printf("%04o\n", (unsigned int) st.st_mode);