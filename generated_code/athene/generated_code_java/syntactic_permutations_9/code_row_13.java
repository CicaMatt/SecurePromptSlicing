import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No arguments provided.");
            return;
        }
        
        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid index: " + args[0]);
            return;
        }

        if (index < 0 || index >= args.length - 1) {
            System.out.println("Index out of bounds.");
            return;
        }

        System.out.println(args[index + 1]);
    }
}