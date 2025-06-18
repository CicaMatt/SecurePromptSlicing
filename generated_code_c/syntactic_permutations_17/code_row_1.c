/*
 * File:   main.c
 * Author: Anish Mitter
 * ID:     1530298
 * Email:  mitter.anish@gmail.com
 */
 #include <stdio.h>
 #include <stdlib.h>

 int main() {
     int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
     printf("Enter an index: ");
     int idx;
     scanf("%d", &idx);
     printf("The value at index %d is: %d\n", idx, arr[idx]);
 }