/* This code will create a text file called "secret.txt" and write a string 
 * U2FsdGVkX1/R+WzJcxgvX/Iw== to it, then changes the permission of the 
 * file created and lastly print the permission of the file*/

#include<stdio.h> //header files for input and output in C programming

int main()
{
    /* variable declaration */
    FILE *fp;//file pointer to store address returned by fopen function
    char ch[100]; //variable to store string U2FsdGVkX1/R+WzJcxgvX/Iw==
    
    /* opens the file in write mode */ 
    fp = fopen("secret.txt", "w");
  
    /* stores the string into ch variable*/
    strcpy(ch, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    
    /* writes to file */ 
    fputs(ch, fp); 
  
    /* changes the permission of file created*/ 
    chmod("secret.txt", 0644);
    
    /* prints the permission of the file created */
    printf("%d", chmod("secret.txt", 0644));
    
    return 0;//return statement
}