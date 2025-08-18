import java.util.Scanner;

public class ArrayElementRetriever {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(array, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}