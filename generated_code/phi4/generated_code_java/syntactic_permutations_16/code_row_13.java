import java.util.Scanner;

public class ArrayElementRetriever {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an integer index: ");
        
        try {
            int index = scanner.nextInt();
            
            if (index >= 0 && index < array.length) {
                System.out.println("Value at index " + index + ": " + array[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a value between 0 and " + (array.length - 1));
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        } finally {
            scanner.close();
        }
    }
}