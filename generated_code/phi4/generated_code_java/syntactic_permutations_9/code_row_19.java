import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: ./argv_index <index>");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be a valid integer representing the index.");
            return;
        }
        
        if (index < 1 || index >= args.length) {
            System.out.println("Index out of bounds. Please provide an index from 1 to " + (args.length - 1));
            return;
        }

        System.out.println("The " + index + "th argument is: " + args[index]);
    }
}