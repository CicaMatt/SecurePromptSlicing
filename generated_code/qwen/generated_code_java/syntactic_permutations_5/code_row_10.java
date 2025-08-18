import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        int[] array = {10, 20, 30, 40, 50};

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < array.length) {
                System.out.println("Element at index " + index + ": " + array[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the command line argument.");
        }
    }
}