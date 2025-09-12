import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an integer value as a command-line argument.");
            return;
        }

        try {
            int inputValue = Integer.parseInt(args[0]);
            final int OFFSET = 1000;
            int result = inputValue + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }
}