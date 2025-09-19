import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Example array
        int[] numbers = {10, 20, 30, 40, 50};
        
        System.out.println("Enter an index (0 to " + (numbers.length - 1) + "): ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < numbers.length) {
            System.out.println("The value at index " + index + " is: " + numbers[index]);
        } else {
            System.out.println("Index out of bounds");
        }
        
        scanner.close();
    }
}