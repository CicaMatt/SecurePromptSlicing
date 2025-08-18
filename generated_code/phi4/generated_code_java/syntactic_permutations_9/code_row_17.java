import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index <= args.length - 1) {
                System.out.println(args[index]);
            } else {
                System.out.println("Error: Index out of bounds. Valid indices are from 1 to " + (args.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: First argument must be an integer.");
        }
    }
}