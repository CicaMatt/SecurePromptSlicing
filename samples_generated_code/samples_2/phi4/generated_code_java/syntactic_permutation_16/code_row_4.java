import java.util.Scanner;

public class ArrayValueAtIndex {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int inputIndex = scanner.nextInt();

        if (inputIndex >= 0 && inputIndex < array.length) {
            System.out.println("Value at index " + inputIndex + ": " + array[inputIndex]);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }
}