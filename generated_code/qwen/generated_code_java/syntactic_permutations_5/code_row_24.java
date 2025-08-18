import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        if (args.length == 0) {
            System.out.println("Please provide an index as a command line argument.");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds. Please provide an index between 0 and " + (elements.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
    }
}