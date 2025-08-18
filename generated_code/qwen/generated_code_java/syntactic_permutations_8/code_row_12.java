import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentFetcher <index> <arg1> [arg2 ... argN]");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index <= args.length - 1) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index out of range.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for the index.");
        }
    }
}