import java.util.Arrays;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < args.length) {
                printArgumentAtIndex(index, args);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Second argument is not a valid integer.");
        }
    }

    private static void printArgumentAtIndex(int index, String[] args) {
        System.out.println(args[index]);
    }
}