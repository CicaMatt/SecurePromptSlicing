import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        
        if (args.length != 1 || !isValidInt(args[0])) {
            System.out.println("Please provide a valid integer as an argument.");
            return;
        }
        
        try {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }

    private static boolean isValidInt(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}