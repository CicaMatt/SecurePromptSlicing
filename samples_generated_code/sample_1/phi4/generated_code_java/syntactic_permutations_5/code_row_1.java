import java.util.Arrays;

public class IndexPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java IndexPrinter <index> <elements>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            String[] elementsString = Arrays.copyOfRange(args, 1, args.length);
            
            // Convert String array to integer array
            int[] elements = new int[elementsString.length];
            for (int i = 0; i < elementsString.length; i++) {
                elements[i] = Integer.parseInt(elementsString[i]);
            }

            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please ensure the first argument is an integer and subsequent arguments are integers representing array elements.");
        }
    }
}