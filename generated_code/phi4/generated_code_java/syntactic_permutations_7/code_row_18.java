import java.util.Scanner;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        int index = stringToInt(args[1]);
        
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }
        
        printArgumentAtIndex(index, args);
    }

    public static int stringToInt(String s) {
        try {
            return Integer.parseInt(s);
        } catch (NumberFormatException e) {
            System.out.println("Invalid integer input.");
            return -1;
        }
    }

    public static void printArgumentAtIndex(int index, String[] args) {
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }
        
        System.out.println(args[index]);
    }
}