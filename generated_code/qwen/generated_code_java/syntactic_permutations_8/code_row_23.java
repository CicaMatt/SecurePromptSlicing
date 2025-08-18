import java.util.Arrays;

public class CommandLineArgumentIndexer {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentIndexer <index> <list of strings>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            String[] values = Arrays.copyOfRange(args, 1, args.length);
            if (index >= 0 && index < values.length) {
                System.out.println(values[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer representing the index.");
        }
    }
}