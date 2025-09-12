import java.util.Arrays;
import java.util.Scanner;

public class FindIndexInArray {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an integer: ");
        int input = scanner.nextInt();
        
        if (input >= 0 && input < array.length) {
            System.out.println("Element at index " + input + ": " + array[input]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}