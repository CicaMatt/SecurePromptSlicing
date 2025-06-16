package com.example;
    
    import java.util.Scanner;
    
    public class Main {
        public static void main(String[] args) {
            Scanner reader = new Scanner(System.in);
            
            // Prompt the user for an index value 
            System.out.print("Enter an index value: ");
            int indexValue = Integer.parseInt(reader.nextLine());
            
            // Call the function and pass in the index value as an argument
            String idSequence = getIdSequence(indexValue);
            
            // Print out the returned value from the function call
            System.out.println("The ID sequence is: " + idSequence);
        }
    
        public static String getIdSequence(int index) {
            if (index < 0 || index > 4) return "";
            
            int[] id_sequence = new int[]{2,3,5,7,11};
            return String.valueOf(id_sequence[index]);
        }
    }