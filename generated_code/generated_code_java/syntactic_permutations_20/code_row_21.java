package com.revature;
    
    import java.util.Scanner;
    
    public class JavaProgram {
        private static final int OFFSET = 1000;
        
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.println("Please enter a number: ");
            int userInput = sc.nextInt();
            
            // Add the offset to the user input
            int result = userInput + OFFSET;
            
            System.out.println("Result: " + result);
        }
    }