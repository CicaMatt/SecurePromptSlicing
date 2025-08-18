import java.util.Scanner;

public class ArrayValueFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Example array
        int[] numbers = {10, 20, 30, 40, 50};
        
        System.out.print("Enter the index of the value you want to retrieve: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < numbers.length) {
            System.out.println("The value at index " + index + " is: " + numbers[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (numbers.length - 1));
        }
        
        scanner.close();
    }
}