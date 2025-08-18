import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                int index = Integer.parseInt(args[0]);
                String result = fetchArgumentByIndex(args, index);
                System.out.println("Value at index " + index + ": " + result);
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer as the first argument.");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("Index out of bounds. Please provide a valid index.");
            }
        } else {
            System.out.println("Usage: java CommandLineArgumentFetcher <index> arg1 arg2 ...");
        }
    }

    public static String fetchArgumentByIndex(String[] argv, int dex) {
        return argv[dex];
    }
}