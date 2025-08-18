import java.util.Scanner;

public class ArrayValueRetriever {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70}; // Example array
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an integer index: ");
        int inputIndex = scanner.nextInt();
        
        if (inputIndex >= 0 && inputIndex < array.length) {
            System.out.println("Value at index " + inputIndex + ": " + array[inputIndex]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and " + (array.length - 1));
        }

        scanner.close();
    }
}