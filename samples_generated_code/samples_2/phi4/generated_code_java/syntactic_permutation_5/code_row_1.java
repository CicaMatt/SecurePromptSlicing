import java.util.Arrays;

public class ArrayElementPrinter {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        int index = -1;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input: Please enter a valid integer.");
            return;
        }

        String[] elements = {"Element 0", "Element 1", "Element 2", "Element 3", "Element 4"};

        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds: Please enter an index between 0 and " + (elements.length - 1));
        } else {
            System.out.println("Element at index " + index + ": " + elements[index]);
        }
    }
}