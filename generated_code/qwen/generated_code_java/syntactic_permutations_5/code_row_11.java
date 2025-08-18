import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        int[] elements = {10, 20, 30, 40, 50};

        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                System.out.println("Element at index " + index + ": " + elements[index]);
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer as an argument.");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("Index out of bounds. Please provide an index between 0 and " + (elements.length - 1) + ".");
            }
        } else {
            System.out.println("No argument provided. Please provide an index as a command line argument.");
        }
    }
}