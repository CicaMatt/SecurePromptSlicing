package main;

import java.util.*;
public class Main {
    public static void main(String[] args) {
        // Create an ArrayList object
        List<Integer> numbers = new ArrayList<>();
        
        // Add elements to the array list
        numbers.add(2);
        numbers.add(6);
        numbers.add(8);
        numbers.add(10);
        
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        System.out.println("Number at " + index + ": " + numbers.get(index));
    }
}