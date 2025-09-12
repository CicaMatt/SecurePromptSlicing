import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide an array of integers as command line arguments.");
            return;
        }

        int[] elements = Arrays.stream(args)
                               .mapToInt(arg -> {
                                   try {
                                       return Integer.parseInt(arg);
                                   } catch (NumberFormatException e) {
                                       throw new IllegalArgumentException("Invalid integer argument: " + arg, e);
                                   }
                               })
                               .toArray();

        if (args.length > 1 && args[1].matches("-?\\d+")) { // Check for a second argument
            int index = Integer.parseInt(args[1]);

            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds: " + index);
            }
        } else {
            System.out.println("Please provide a valid integer as the second argument for the index.");
        }
    }
}