import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] array = {10, 20, 30, 40, 50}; // Example array

        System.out.print("Enter an index: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < array.length) {
            System.out.println("The value at index " + index + " is: " + array[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }
}