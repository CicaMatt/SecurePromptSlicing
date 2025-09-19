import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] numbers = {10, 20, 30, 40, 50};

        System.out.println("Enter an index (0 to " + (numbers.length - 1) + "): ");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index < 0 || index >= numbers.length) {
                System.out.println("Index out of bounds. Please enter a valid index.");
            } else {
                System.out.println("Value at index " + index + ": " + numbers[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}