import java.util.Arrays;

public class CommandLineArgumentIndex {
    public static void main(String[] args) {
        if (args.length < 2 || !args[1].matches("\\d+")) {
            System.out.println("Please provide a valid index as the second argument.");
            return;
        }

        int index = Integer.parseInt(args[1]);

        if (index >= args.length || index < 0) {
            System.out.println("Index out of bounds.");
            return;
        }

        System.out.println("Value at index " + index + ": " + args[index]);
    }
}