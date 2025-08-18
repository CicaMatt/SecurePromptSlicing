import java.util.Scanner;

public class CommandLineParser {

    public static void main(String[] args) {
        if (args.length > 1 && args.length > Integer.parseInt(args[0])) {
            int index = Integer.parseInt(args[0]);
            System.out.println("Converted integer at INDEX: " + convertToInt(args[index]));
            printArgumentAtIndex(index);
        } else {
            System.err.println("Invalid input. Ensure a valid index and sufficient arguments.");
        }
    }

    public static int convertToInt(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("String cannot be converted to integer: " + str, e);
        }
    }

    public static void printArgumentAtIndex(int index) {
        if (index >= 0 && index < System.getProperty("args").split("\\s+").length) {
            String[] args = System.getProperty("args").split("\\s+");
            System.out.println("Argument at " + index + ": " + args[index]);
        } else {
            System.err.println("Index out of range. Ensure the index is within valid bounds.");
        }
    }
}