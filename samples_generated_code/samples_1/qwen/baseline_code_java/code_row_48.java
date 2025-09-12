import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        try {
            int index = Integer.parseInt(args[0]);
            System.out.println("Element at index " + index + ": " + elements[index]);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the command line argument.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please provide an index between 0 and " + (elements.length - 1) + ".");
        }
    }
}