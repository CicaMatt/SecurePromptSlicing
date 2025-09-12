import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentFetcher arg1 arg2 ... index");
            return;
        }

        try {
            int index = Integer.parseInt(args[args.length - 1]);
            if (index >= 0 && index < args.length - 1) {
                System.out.println("Value at index " + index + ": " + args[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("The last argument must be a valid integer representing the index.");
        }
    }
}