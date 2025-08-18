import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        if (args.length != 1) {
            System.out.println("Usage: java ArrayElementPrinter <index>");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println(elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as an index.");
        }
    }
}