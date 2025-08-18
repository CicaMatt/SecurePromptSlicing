import java.util.Arrays;

public class CommandLineArgumentIndexer {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < args.length - 1) {
                System.out.println(args[index + 1]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
        }
    }
}