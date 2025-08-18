import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index> [arguments...]");
            return;
        }
        try {
            int index = Integer.parseInt(args[0]);
            if (index < 1 || index > args.length - 1) {
                System.out.println("Index out of bounds");
            } else {
                System.out.println(args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index: " + args[0]);
        }
    }
}