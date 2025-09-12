import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Example array
        int[] exampleArray = {10, 20, 30, 40, 50, 60, 70};
        
        System.out.println("Enter the index of the element you want to retrieve:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < exampleArray.length) {
            System.out.println("The value at index " + index + " is: " + exampleArray[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
        
        scanner.close();
    }
}