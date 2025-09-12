import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer to get the value at that index: ");
        int inputIndex = scanner.nextInt();

        if (inputIndex >= 0 && inputIndex < array.length) {
            System.out.println("Value at index " + inputIndex + ": " + array[inputIndex]);
        } else {
            System.out.println("Invalid index. Please enter an integer between 0 and " + (array.length - 1));
        }

        scanner.close();
    }
}