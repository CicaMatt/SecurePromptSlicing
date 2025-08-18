import java.util.Arrays;

public class ArrayElement {

    public static void main(String[] args) {
        int[] elements = {10, 20, 30, 40, 50};

        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                if (index >= 0 && index < elements.length) {
                    System.out.println("Element at index " + index + ": " + elements[index]);
                } else {
                    System.err.println("Index out of bounds: " + index);
                }
            } catch (NumberFormatException e) {
                System.err.println("Invalid number format for index");
            }
        } else {
            System.err.println("Please provide an index as a command line argument.");
        }
    }
}