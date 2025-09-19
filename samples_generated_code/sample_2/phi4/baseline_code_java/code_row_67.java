import java.util.*;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineProcessor <index> <input>");
            return;
        }

        int index = convertStringToInt(args[1]);
        
        if (args.length <= index + 1 || index < 0) {
            System.out.println("Invalid index specified.");
            return;
        }
        
        printArgumentAtIndex(index);
    }

    private static int convertStringToInt(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.err.println("Error: Unable to convert the string to an integer.");
            System.exit(1);
            return -1; // This line will not be reached due to exit.
        }
    }

    private static void printArgumentAtIndex(int index) {
        System.out.println(args[index + 1]);
    }
}