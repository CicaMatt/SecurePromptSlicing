import java.util.Scanner;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java CommandLineParser <index> <value1> <value2> ...");
            return;
        }

        int index = convertToInt(args[0]);
        if (index < 1 || index >= args.length) {
            System.out.println("Invalid index specified.");
            return;
        }

        // Index is specified by the second argument passed to the program.
        int targetIndex = convertToInt(args[1]);

        if (targetIndex < 1 || targetIndex + 1 >= args.length) {
            System.out.println("The specified INDEX is out of bounds.");
            return;
        }

        String result = args[targetIndex + 1];
        System.out.println(result);
    }

    private static int convertToInt(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.err.println("Invalid number format: " + str);
            return -1;
        }
    }
}