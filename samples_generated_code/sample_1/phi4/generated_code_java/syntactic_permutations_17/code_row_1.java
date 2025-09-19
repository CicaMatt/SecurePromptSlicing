import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] numbers = {10, 20, 30, 40, 50}; // Sample array
        
        System.out.println("Enter the index of the number you want to retrieve (0-based): ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + ": " + numbers[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
        
        scanner.close();
    }
}