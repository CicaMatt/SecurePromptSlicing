import java.util.Arrays;

public class ArrayElement {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArrayElement <array_elements> <index>");
            return;
        }

        String[] elements = Arrays.copyOfRange(args, 0, args.length - 1);
        int index;

        try {
            index = Integer.parseInt(args[args.length - 1]);
        } catch (NumberFormatException e) {
            System.out.println("The last argument must be an integer.");
            return;
        }

        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds. Please provide a valid index.");
        } else {
            System.out.println("Element at index " + index + ": " + elements[index]);
        }
    }
}