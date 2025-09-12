import java.util.Arrays;

public class ArrayElementAccess {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArrayElementAccess <size> <index>");
            return;
        }

        try {
            int size = Integer.parseInt(args[0]);
            int index = Integer.parseInt(args[1]);

            int[] array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = i + 1; // Fill the array with sequential numbers starting from 1
            }

            if (index >= 0 && index < size) {
                System.out.println("Element at index " + index + ": " + array[index]);
            } else {
                System.out.println("Index out of bounds. Please provide an index between 0 and " + (size - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide valid integer arguments.");
        }
    }
}