import java.util.Scanner;

public class CommandLineStringToInt {

    public static void main(String[] args) {
        if (args.length < 2 || !isInteger(args[1])) {
            System.out.println("Invalid input.");
            return;
        }

        int index = Integer.parseInt(args[1]);

        if (index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        String commandLineArgumentAtSpecifiedIndex = args[index];
        printStringAtIndex(index);
    }

    public static boolean isInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static void printStringAtIndex(int index) {
        System.out.println("The string at position " + index + " is: " + args[index]);
    }
}