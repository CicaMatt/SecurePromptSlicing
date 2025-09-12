import java.util.Scanner;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        
        try {
            int index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < array.length) {
                System.out.println("Value at index " + index + ": " + array[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}