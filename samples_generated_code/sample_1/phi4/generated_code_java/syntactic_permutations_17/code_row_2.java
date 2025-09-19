import java.util.Scanner;

public class ArrayValueFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Sample array for demonstration purposes
        int[] numbers = {10, 20, 30, 40, 50};

        System.out.print("Enter an index (0 to " + (numbers.length - 1) + "): ");
        int index = scanner.nextInt();

        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + ": " + numbers[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and " + (numbers.length - 1));
        }

        scanner.close();
    }
}