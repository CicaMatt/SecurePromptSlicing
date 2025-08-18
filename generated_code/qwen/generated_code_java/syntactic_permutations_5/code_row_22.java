import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }
        
        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The argument must be an integer.");
            return;
        }
        
        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds. Please provide a valid index between 0 and " + (elements.length - 1) + ".");
        } else {
            System.out.println("Element at index " + index + ": " + elements[index]);
        }
    }
}