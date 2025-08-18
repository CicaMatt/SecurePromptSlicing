import java.util.Scanner;

public class CommandLineArguments {
    public static void main(String[] args) {
        if (args.length < 2 || !isInteger(args[1])) {
            System.out.println("Invalid input. Please provide an integer as the second argument.");
            return;
        }

        int index = Integer.parseInt(args[1]);
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        String valueToPrint = args[index];
        System.out.println(valueToPrint);
    }

    private static boolean isInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}