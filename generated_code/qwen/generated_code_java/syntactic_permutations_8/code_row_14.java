import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two arguments.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer representing an index.");
            return;
        }

        if (index < 0 || index >= args.length - 2) {
            System.out.println("Index out of bounds. Please provide a valid index.");
            return;
        }

        String result = args[index + 2];
        System.out.println("Value at index " + index + ": " + result);
    }
}