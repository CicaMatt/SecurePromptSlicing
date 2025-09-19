import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer for the index: ");
        
        try {
            int inputIndex = scanner.nextInt();
            
            if (inputIndex < 0 || inputIndex >= array.length) {
                System.out.println("Index out of bounds");
            } else {
                System.out.println("Value at index " + inputIndex + ": " + array[inputIndex]);
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        } finally {
            scanner.close();
        }
    }
}