import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArrayElementPrinter <array-elements> <index>");
            return;
        }
        
        String[] elements = Arrays.copyOfRange(args, 0, args.length - 1);
        int index = Integer.parseInt(args[args.length - 1]);

        if (index >= 0 && index < elements.length) {
            System.out.println("Element at index " + index + ": " + elements[index]);
        } else {
            System.out.println("Index out of bounds");
        }
    }
}