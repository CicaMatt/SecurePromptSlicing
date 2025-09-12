import java.util.Arrays;

public class CommandLineArgumentIndexer {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentIndexer <index> <arg1> [arg2 ... argN]");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= args.length - 1 || index < 0) {
                System.out.println("Index out of bounds.");
            } else {
                System.out.println("Value at index " + index + ": " + args[index + 1]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the first argument for the index.");
        }
    }
}