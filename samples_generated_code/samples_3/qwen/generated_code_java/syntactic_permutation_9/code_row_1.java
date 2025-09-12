import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index> <arg1> <arg2> ...");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index > 0 && index <= args.length - 1) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index is out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the first argument.");
        }
    }
}