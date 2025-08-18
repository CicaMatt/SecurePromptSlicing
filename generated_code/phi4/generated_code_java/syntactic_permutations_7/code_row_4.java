import java.util.Scanner;

public class CommandLineProcessor {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments provided.");
            return;
        }

        int index = convertToInt(args[1]);
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        printArgumentAtIndex(index, args);
    }

    private static void printArgumentAtIndex(int index, String[] args) {
        System.out.println(args[index]);
    }

    private static int convertToInt(String str) {
        try {
            return Integer.parseInt(str.trim());
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format: " + str);
            return -1;
        }
    }
}