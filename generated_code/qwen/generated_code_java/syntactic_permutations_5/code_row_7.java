import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
            return;
        }

        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};

        if (index >= 0 && index < elements.length) {
            System.out.println("Element at index " + index + ": " + elements[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}