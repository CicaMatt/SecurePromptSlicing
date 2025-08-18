import java.util.Arrays;

public class IndexPrinter {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java IndexPrinter <index> <comma-separated-list>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            String[] elements = args[1].split(",");
            if (index >= 0 && index < elements.length) {
                System.out.println(elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index. Please provide a valid integer.");
        }
    }
}