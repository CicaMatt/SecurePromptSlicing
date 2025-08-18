import java.util.Scanner;

public class ArrayIndexPrinter {
    public static void main(String[] args) {
        int[] elements = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an index to print the element:");
        String input = scanner.nextLine();
        
        try {
            int index = Integer.parseInt(input);
            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer.");
        }
        
        scanner.close();
    }
}