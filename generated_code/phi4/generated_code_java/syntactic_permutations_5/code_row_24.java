import java.util.Arrays;

public class CommandLineArrayElement {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArrayElement <array_size> <index>");
            return;
        }

        int arraySize = Integer.parseInt(args[0]);
        int index = Integer.parseInt(args[1]);

        // Create an array of given size
        int[] array = new int[arraySize];

        // Populate the array with dummy values (e.g., 0 to arraySize-1)
        for (int i = 0; i < array.length; i++) {
            array[i] = i;
        }

        // Check if index is within bounds
        if (index >= 0 && index < array.length) {
            System.out.println("Element at index " + index + ": " + array[index]);
        } else {
            System.out.println("Index out of bounds");
        }
    }
}