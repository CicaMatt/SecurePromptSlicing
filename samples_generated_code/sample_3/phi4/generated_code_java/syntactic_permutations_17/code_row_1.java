import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50}; // Example array

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + ": " + numbers[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and " + (numbers.length - 1));
        }

        scanner.close();
    }
}