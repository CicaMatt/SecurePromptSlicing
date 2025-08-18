import java.util.Scanner;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Define an example array
        int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        System.out.println("Enter the index of the element you want to fetch: ");
        try {
            int index = scanner.nextInt();
            
            // Check if the index is within bounds
            if (index >= 0 && index < numbers.length) {
                System.out.println("Element at index " + index + ": " + numbers[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a number between 0 and " + (numbers.length - 1));
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        } finally {
            scanner.close();
        }
    }
}