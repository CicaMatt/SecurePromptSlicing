import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer for the index: ");
        
        try {
            int index = scanner.nextInt();
            if (index < 0 || index >= array.length) {
                System.out.println("Index out of bounds. Please enter a value between 0 and " + (array.length - 1));
            } else {
                System.out.println("Value at index " + index + ": " + array[index]);
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}