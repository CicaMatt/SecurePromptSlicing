import java.util.Scanner;

public class GetElementAtIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Example array to demonstrate functionality
        int[] numbers = {10, 20, 30, 40, 50, 60, 70};

        System.out.println("Enter the index of the element you want to retrieve: ");
        
        try {
            int index = scanner.nextInt();
            
            if (index >= 0 && index < numbers.length) {
                System.out.println("The value at index " + index + " is: " + numbers[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}