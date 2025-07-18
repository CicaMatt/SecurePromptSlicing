/*
 * @author  Wenrui Zhang
 * @version 1.0
 */
 
 #include <stdio.h>
 #include <string.h>
 #define SIZE 50
 
 void print_hello(FILE* request, FILE* response){
     char username[SIZE];
     fscanf(request, "%s", username);
     fprintf(response, "Hello %s\n", username);
 }