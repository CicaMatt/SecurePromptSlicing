import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index < 1 || index >= args.length) {
                System.out.println("Index out of bounds. Please provide a valid index between 1 and " + (args.length - 1));
                return;
            }
            System.out.println(args[index]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer representing the index.");
        }
    }
}