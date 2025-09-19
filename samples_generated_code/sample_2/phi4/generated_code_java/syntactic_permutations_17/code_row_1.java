import java.util.Scanner;

public class ArrayValueAtIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] array = {10, 20, 30, 40, 50};
        System.out.println("Array: " + java.util.Arrays.toString(array));
        
        System.out.print("Enter the index to retrieve value from the array (0 to 4): ");
        int index;
        while (true) {
            try {
                index = scanner.nextInt();
                if (index >= 0 && index < array.length) {
                    break;
                } else {
                    System.out.println("Index out of bounds. Please enter a valid index (0 to 4).");
                }
            } catch (Exception e) {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.next(); // clear the invalid input
            }
        }

        System.out.println("Value at index " + index + ": " + array[index]);
        
        scanner.close();
    }
}