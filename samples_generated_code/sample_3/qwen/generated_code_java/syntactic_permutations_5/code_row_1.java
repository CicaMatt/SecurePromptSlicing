import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"zero", "one", "two", "three", "four", "five"};
        
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[0]);
            if (index < 0 || index >= elements.length) {
                System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (elements.length - 1));
            } else {
                System.out.println("Element at index " + index + ": " + elements[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide an integer.");
        }
    }
}