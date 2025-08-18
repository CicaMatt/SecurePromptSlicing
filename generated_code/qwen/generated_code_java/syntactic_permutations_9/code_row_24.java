import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an index and at least one argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index > 0 && index <= args.length - 1) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index out of range. Please provide a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index provided. Please enter a numeric value.");
        }
    }
}