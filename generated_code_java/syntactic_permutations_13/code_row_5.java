package com.mycompany;
import java.util.*; //Importing util package

public class Main { // Creating Main class
    public static void main(String[] args) { // Declaring Main function
        Scanner input = new Scanner(System.in);//Scanning input from user
        System.out.println("Enter an index value: "); //Prompting user for index value
        int x = input.nextInt(); // Assigning the next integer to x 
        int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // Declaring array with id_sequence values
        
        System.out.println(getValue(id_sequence, x)); // Calling getValue function to print the value at index x in id_sequence
    }
    public static int getValue(int[] id_sequence, int x){  // Declaring getValue function and returning value at index x
        return id_sequence[x];
    }
}