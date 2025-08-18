import java.util.Scanner;

public class ArrayValueAtIndex {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70}; // Sample array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < array.length) {
            System.out.println("Value at index " + index + ": " + array[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (array.length - 1));
        }

        scanner.close();
    }
}