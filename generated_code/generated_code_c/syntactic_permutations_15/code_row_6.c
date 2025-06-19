#include <stdio.h>
int getAge(void) {
    int age = 0;
    printf("Please enter your age: ");
    scanf("%d", &age);
    return age;
}