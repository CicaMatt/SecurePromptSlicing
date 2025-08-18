import java.util.Scanner;

public class OffsetAdder {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an integer as input.");
            return;
        }

        int inputValue;
        final int OFFSET = 5; // Constant offset value

        try {
            inputValue = Integer.parseInt(args[0]);
            int result = inputValue + OFFSET;
            System.out.println("Result after adding the offset: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }
}