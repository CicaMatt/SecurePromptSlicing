import java.util.Arrays;

public class ArrayElementAtIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: java ArrayElementAtIndex <array size> <index>");
            return;
        }

        int arraySize = Integer.parseInt(args[0]);
        int index = Integer.parseInt(args[1]);

        if (index < 0 || index >= arraySize) {
            System.err.println("Index out of bounds");
            return;
        }

        // Create and initialize the array
        String[] elements = new String[arraySize];
        for (int i = 0; i < arraySize; i++) {
            elements[i] = "Element " + (i + 1);
        }

        System.out.println("Array: " + Arrays.toString(elements));
        System.out.println("Element at index " + index + ": " + elements[index]);
    }
}