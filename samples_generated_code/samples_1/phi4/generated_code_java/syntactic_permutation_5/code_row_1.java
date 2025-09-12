import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        // Create an array with some elements
        int[] array = {10, 20, 30, 40, 50};

        // Check if a command line argument is provided
        if (args.length > 0) {
            try {
                // Convert the first argument to an integer index
                int index = Integer.parseInt(args[0]);

                // Check if the index is within the bounds of the array
                if (index >= 0 && index < array.length) {
                    // Print the element at the specified index
                    System.out.println("Element at index " + index + ": " + array[index]);
                } else {
                    System.out.println("Index out of bounds.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please provide a valid integer index.");
            }
        } else {
            System.out.println("Please provide an index as a command line argument.");
        }
    }
}