import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] numbers = {10, 20, 30, 40, 50}; // Example array

        System.out.print("Enter the index of the number you want to retrieve: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < numbers.length) {
            System.out.println("The value at index " + index + " is: " + numbers[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }
}