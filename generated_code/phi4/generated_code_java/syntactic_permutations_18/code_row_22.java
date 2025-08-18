import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + ": " + numbers[index]);
        } else {
            System.out.println("Index out of bounds!");
        }

        scanner.close();
    }
}