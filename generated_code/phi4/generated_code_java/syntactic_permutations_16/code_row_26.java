import java.util.Scanner;

public class ArrayValueRetriever {
    public static void main(String[] args) {
        int[] arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an integer to get the value at that index: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < arr.length) {
            System.out.println("Value at index " + index + ": " + arr[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }
}