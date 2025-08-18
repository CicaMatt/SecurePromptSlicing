import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] array = {10, 20, 30, 40, 50}; // Example array

        System.out.print("Enter an integer index: ");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(array, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }
    
    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}