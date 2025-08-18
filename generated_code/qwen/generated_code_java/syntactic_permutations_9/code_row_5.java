import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an index and at least one argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]) - 1;
            if (index >= 0 && index < args.length - 1) {
                System.out.println(args[index + 1]);
            } else {
                System.out.println("Index out of range.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the first argument.");
        }
    }
}