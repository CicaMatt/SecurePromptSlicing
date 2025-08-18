import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an integer index: ");
        int inputIndex = scanner.nextInt();

        if (inputIndex >= 0 && inputIndex < array.length) {
            System.out.println("Value at index " + inputIndex + ": " + array[inputIndex]);
        } else {
            System.out.println("Invalid index. Please enter a value between 0 and " + (array.length - 1));
        }

        scanner.close();
    }
}