import java.util.Arrays;

public class CommandLineArgumentIndexer {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentIndexer <index> <arg1> [arg2...]");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index out of bounds. Please provide a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index provided. Please provide an integer as the first argument.");
        }
    }
}