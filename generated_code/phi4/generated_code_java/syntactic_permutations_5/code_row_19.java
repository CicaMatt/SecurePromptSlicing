import java.util.Arrays;

public class ArrayElement {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArrayElement <array_size> <index>");
            return;
        }

        try {
            int arraySize = Integer.parseInt(args[0]);
            int index = Integer.parseInt(args[1]);

            int[] array = new int[arraySize];
            Arrays.fill(array, 1); // Fill the array with some default values

            if (index >= 0 && index < array.length) {
                System.out.println("Element at index " + index + ": " + array[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Both arguments must be integers.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Usage: java ArrayElement <array_size> <index>");
        }
    }
}