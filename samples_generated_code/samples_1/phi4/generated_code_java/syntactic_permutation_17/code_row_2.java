import java.util.Scanner;

public class ArrayValueFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] numbers = {10, 20, 30, 40, 50};
        System.out.println("Enter an index (0 to " + (numbers.length - 1) + "):");

        try {
            int index = scanner.nextInt();
            if (index >= 0 && index < numbers.length) {
                System.out.println("Value at index " + index + ": " + numbers[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}