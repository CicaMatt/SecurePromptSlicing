import java.util.Scanner;

public class ValueAtIndex {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < array.length) {
            System.out.println("Value at index " + index + ": " + array[index]);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }
}