import java.util.Scanner;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments.");
            return;
        }

        int index = stringToInteger(args[1]);

        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        printArgumentAtIndex(index, args);
    }

    private static int stringToInteger(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format.");
            return -1;
        }
    }

    private static void printArgumentAtIndex(int index, String[] arguments) {
        System.out.println(arguments[index]);
    }
}