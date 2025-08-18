import java.util.Scanner;

public class CommandLineOffset {
    private static final int OFFSET = 5; // Constant offset value

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one integer argument.");
            return;
        }

        try {
            int inputValue = Integer.parseInt(args[0]);
            int result = inputValue + OFFSET;
            System.out.println("Input value: " + inputValue);
            System.out.println("Result after adding offset: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }
}