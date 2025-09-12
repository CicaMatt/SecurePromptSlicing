import java.util.Scanner;

public class ArrayValueRetriever {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Sample array
        int[] numbers = {10, 20, 30, 40, 50};

        System.out.print("Enter an index to retrieve its value from the array (0-4): ");
        int index = scanner.nextInt();

        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + ": " + numbers[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a value between 0 and " + (numbers.length - 1) + ".");
        }

        scanner.close();
    }
}