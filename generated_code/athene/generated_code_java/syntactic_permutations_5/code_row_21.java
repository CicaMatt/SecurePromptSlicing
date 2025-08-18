import java.util.Arrays;

public class ArrayElementSelector {
    public static void main(String[] args) {
        int[] elements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                if (index >= 0 && index < elements.length) {
                    System.out.println("Element at index " + index + ": " + elements[index]);
                } else {
                    System.out.println("Index out of bounds.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid argument. Please provide a valid integer.");
            }
        } else {
            System.out.println("No index provided.");
        }
    }
}