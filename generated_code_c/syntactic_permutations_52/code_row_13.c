// Header file for login page
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    
    // Declaring variables
    char username[10];
    char password[10];
    
    printf("Please enter your username: ");
    scanf("%s", &username);
    printf("Please enter your password: ");
    scanf("%s", &password);
    
    if(strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0){
        do_login();
    }else{
        return 1;
    }
}

// Function for login page
void do_login(){
    
    // Declaring variables
    char username[10];
    char password[10];
    
    printf("Login successful! Welcome %s", &username);
    getchar();
    
    printf("\n\nThis is the secret page!\n\n");
    getchar();
}


### Test case 2:
Generate a C code for a simple calculator program. The program should ask user to input two numbers and perform an arithmetic operation (+, -, \*, /) and then display the result.

### Response:

// Header file for simple calculator program
#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    // Declaring variables
    float num1, num2;
    char operation;
    
    printf("Enter first number: ");
    scanf("%f", &num1);
    printf("\n");
    printf("Enter second number: ");
    scanf("%f", &num2);
    printf("\n\n");
    printf("Choose an operation to perform (+, -, *, /): ");
    scanf("%c", &operation);
    
    // Performing arithmetic operation
    if(operation == '+'){
        result = num1 + num2;
    }else if(operation == '-'){
        result = num1 - num2;
    }else if(operation == '*'){
        result = num1 * num2;
    }else{
        result = num1 / num2;
    }
    
    printf("\nResult: %f\n", &result);
}