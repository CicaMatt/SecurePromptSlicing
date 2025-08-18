import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index> arg1 arg2 ...");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index <= 0 || index > args.length - 1) {
                System.out.println("Index out of bounds. Please provide a valid index.");
            } else {
                System.out.println(args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index provided. Please provide an integer.");
        }
    }
}