import java.util.Arrays;

public class CommandLineArguments {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index < 0 || index >= args.length) {
                System.out.println("Index out of bounds.");
                return;
            }
            System.out.println("Value at the provided index: " + args[index]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer representing an index.");
        }
    }
}