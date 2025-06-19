package com.example;
    
    import java.util.*;

    public class Main {
      public static void main(String[] args) {
        String [] id_sequence = {"1", "2" , "3", "4"};
        int index;
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index between 0 and 3: ");
        index=scanner.nextInt();
        
        if (index<0 || index>3){
          System.out.println("Invalid input.");
        } else {
            String result = id_sequence[index];
            System.out.println("The value at index " + index+ " is: " + result);
        }
      } 
    }