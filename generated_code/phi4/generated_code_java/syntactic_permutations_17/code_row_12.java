import java.util.Scanner;

public class ArrayValueFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Define an example array
        int[] numbers = {10, 20, 30, 40, 50};

        System.out.print("Enter a number (0 to " + (numbers.length - 1) + ") to find its value in the array: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + " is: " + numbers[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a number between 0 and " + (numbers.length - 1));
        }

        scanner.close();
    }
}