import java.util.Arrays;

public class ArrayElementAccess {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an array size as a command line argument.");
            return;
        }

        int arraySize = Integer.parseInt(args[0]);
        String[] elements = new String[arraySize];

        // Populate the array with sample data
        for (int i = 0; i < arraySize; i++) {
            elements[i] = "Element" + (i + 1);
        }
        
        System.out.println("Array: " + Arrays.toString(elements));

        if (args.length < 2) {
            System.out.println("Please provide an index as a second command line argument.");
            return;
        }

        int index = Integer.parseInt(args[1]);

        if (index >= 0 && index < arraySize) {
            System.out.println("Element at index " + index + ": " + elements[index]);
        } else {
            System.out.println("Index out of bounds. Please provide a valid index.");
        }
    }
}