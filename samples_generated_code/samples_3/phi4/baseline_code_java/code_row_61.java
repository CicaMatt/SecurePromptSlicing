import java.util.Arrays;

public class ArrayElement {
    public static void main(String[] args) {
        // Define an array with sample elements
        String[] elements = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};

        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                
                // Check if the index is within bounds of the array
                if (index >= 0 && index < elements.length) {
                    System.out.println("Element at index " + index + ": " + elements[index]);
                } else {
                    System.out.println("Index out of bounds. Please provide an index between 0 and " + (elements.length - 1));
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a valid integer.");
            }
        } else {
            System.out.println("Please provide an index as a command line argument.");
        }
    }
}