import java.util.Scanner;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Not enough arguments.");
            return;
        }

        int index = stringToInt(args[1]);
        
        if (index < 0 || index >= args.length) {
            System.out.println("Error: Index out of bounds.");
            return;
        }
        
        printArgumentAtIndex(index, args);
    }

    public static int stringToInt(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid number format.");
            System.exit(1);
            return -1; // This line will never be reached
        }
    }

    public static void printArgumentAtIndex(int index, String[] args) {
        System.out.println(args[index]);
    }
}