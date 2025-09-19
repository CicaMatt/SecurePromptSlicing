import java.util.Scanner;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an index and at least one argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index <= 0 || index >= args.length) {
                System.out.println("Index is out of bounds.");
            } else {
                System.out.println(args[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer representing the index.");
        }
    }
}