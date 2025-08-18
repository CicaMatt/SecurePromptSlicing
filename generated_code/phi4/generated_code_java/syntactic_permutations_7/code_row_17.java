import java.util.Arrays;

public class CommandLineProcessor {

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Insufficient arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            printArgumentAtIndex(args, index);
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer representing the index.");
        }
    }

    private static void printArgumentAtIndex(String[] args, int index) {
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println(args[index]);
        }
    }
}