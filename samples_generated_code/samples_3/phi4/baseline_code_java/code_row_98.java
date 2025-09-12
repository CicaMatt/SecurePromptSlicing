import java.util.Scanner;

public class ArrayValueAtIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] array = {10, 20, 30, 40, 50}; // Example array

        System.out.print("Enter the index of the array: ");
        int index = scanner.nextInt();
        
        try {
            int value = array[index];
            System.out.println("Value at index " + index + ": " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
        
        scanner.close();
    }
}