import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No arguments provided");
            return;
        }
        try {
            int index = Integer.parseInt(args[0]);
            if (index < 0 || index >= args.length - 1) {
                System.out.println("Index out of bounds");
            } else {
                System.out.println(args[index + 1]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index provided");
        }
    }
}