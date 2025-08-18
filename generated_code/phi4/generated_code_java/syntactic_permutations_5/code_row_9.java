import java.util.Arrays;

public class ArrayElement {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50};

        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                if (index >= 0 && index < array.length) {
                    System.out.println("Element at index " + index + ": " + array[index]);
                } else {
                    System.out.println("Index out of bounds.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input: not an integer.");
            }
        } else {
            System.out.println("No command line argument provided.");
        }
    }
}