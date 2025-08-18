import java.util.Scanner;

public class ArrayValueAtIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input size of the array
        System.out.print("Enter the number of elements in the array: ");
        int n = scanner.nextInt();

        // Create and populate the array
        int[] array = new int[n];
        System.out.println("Enter " + n + " integers:");
        for (int i = 0; i < n; i++) {
            array[i] = scanner.nextInt();
        }

        // Input index to retrieve value from
        System.out.print("Enter the index of the element you want to retrieve: ");
        int index = scanner.nextInt();

        // Validate index and print value or error message
        if (index >= 0 && index < n) {
            System.out.println("The value at index " + index + " is: " + array[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (n - 1) + ".");
        }

        scanner.close();
    }
}