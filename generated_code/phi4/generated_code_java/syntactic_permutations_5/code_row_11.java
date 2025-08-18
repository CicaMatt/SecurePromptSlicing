import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        // Create an array of elements
        int[] arr = {10, 20, 30, 40, 50};

        if (args.length > 0) {
            try {
                // Convert the command line argument to an integer
                int index = Integer.parseInt(args[0]);

                // Print the element at that index if within bounds
                if (index >= 0 && index < arr.length) {
                    System.out.println("Element at index " + index + ": " + arr[index]);
                } else {
                    System.out.println("Index out of bounds.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid number format. Please provide a valid integer.");
            }
        } else {
            System.out.println("No command line argument provided.");
        }
    }
}