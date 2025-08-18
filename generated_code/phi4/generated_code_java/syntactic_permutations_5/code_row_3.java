import java.util.Arrays;

public class CommandLineArrayElement {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArrayElement <element1> <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String[] elements = Arrays.copyOfRange(args, 0, args.length);
            
            // Remove the index argument to get only the array elements
            if (elements.length > index) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for the index.");
        }
    }
}