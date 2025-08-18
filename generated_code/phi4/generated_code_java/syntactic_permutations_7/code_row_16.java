import java.util.Scanner;

public class CommandLineArgumentParser {
    public static void main(String[] args) {
        if (args.length < 2 || !isInteger(args[1])) {
            System.out.println("Usage: java CommandLineArgumentParser <index>");
            return;
        }

        int index = Integer.parseInt(args[1]);

        if (args.length <= index) {
            System.out.println("Index out of bounds.");
            return;
        }

        printArgumentAtIndex(index);
    }

    private static boolean isInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    private static void printArgumentAtIndex(int index) {
        System.out.println("The string at position " + index + " is: " + args[index]);
    }
}