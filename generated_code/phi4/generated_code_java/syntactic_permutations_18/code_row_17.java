import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Sample array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        
        if (scanner.hasNextInt()) {
            int index = scanner.nextInt();
            
            if (index >= 0 && index < array.length) { // Check for valid index
                System.out.println("Value at index " + index + ": " + array[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}