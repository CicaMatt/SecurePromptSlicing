import java.util.Scanner;

public class ArrayValueFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] numbers = {10, 20, 30, 40, 50};
        
        System.out.println("Enter the index of the array you want to access (0-4): ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < numbers.length) {
            System.out.println("The value at index " + index + " is: " + numbers[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
        
        scanner.close();
    }
}