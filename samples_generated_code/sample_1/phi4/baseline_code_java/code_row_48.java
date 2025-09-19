import java.util.Arrays;

public class ArrayElement {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an array index as a command line argument.");
            return;
        }

        int[] elements = {10, 20, 30, 40, 50};

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format. Please provide a valid integer.");
        }
    }
}