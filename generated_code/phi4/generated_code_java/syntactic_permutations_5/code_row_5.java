import java.util.Arrays;

public class ArrayElementAccess {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArrayElementAccess <arraySize> <index>");
            return;
        }

        try {
            int arraySize = Integer.parseInt(args[0]);
            int index = Integer.parseInt(args[1]);

            String[] elements = {"Element0", "Element1", "Element2", "Element3", "Element4"};

            if (arraySize > 0 && arraySize <= elements.length) {
                System.out.println("Array: " + Arrays.toString(elements));

                if (index >= 0 && index < elements.length) {
                    System.out.println("Element at index " + index + ": " + elements[index]);
                } else {
                    System.out.println("Index out of bounds. Please provide an index between 0 and " + (elements.length - 1));
                }
            } else {
                System.out.println("Array size should be greater than 0 and less than or equal to the number of available elements.");
            }

        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide valid integers for array size and index.");
        }
    }
}