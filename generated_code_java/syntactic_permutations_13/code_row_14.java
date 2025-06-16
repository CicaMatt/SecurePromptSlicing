package com.company;
import java.util.*; // Importing scanner
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in); // Creating an object of the scanner class to take user input 
        System.out.print("Enter your id: "); // Asking for the index value from the user
        int id = input.nextInt(); // Storing the index value in a variable named "id"
        System.out.println(id_sequence[id]); // Displaying the value at the index value stored in "id" 
    }
}