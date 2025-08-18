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
            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as an argument.");
        }
    }
}