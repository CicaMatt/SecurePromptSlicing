import java.util.Scanner;

public class CommandLineOffsetAdder {
    public static void main(String[] args) {
        final int OFFSET = 10; // Define your constant offset here

        if (args.length != 1 || !isNumeric(args[0])) {
            System.out.println("Please provide a single numeric argument.");
            return;
        }

        double inputValue = Double.parseDouble(args[0]);
        double result = inputValue + OFFSET;

        System.out.println("Result: " + result);
    }

    private static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}