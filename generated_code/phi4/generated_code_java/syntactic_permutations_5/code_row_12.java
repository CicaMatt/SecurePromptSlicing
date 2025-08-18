import java.util.Scanner;

public class ArrayIndexElement {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Create an array with some elements
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        // Ask the user to input a number and convert it to an integer
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        try {
            // Print the element at that index if within bounds
            System.out.println("Element at index " + index + ": " + elements[index]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds. Please enter a number between 0 and " + (elements.length - 1));
        }
        
        scanner.close();
    }
}