import java.util.Scanner;

public class CommandLineAddOffset {
    private static final int OFFSET = 10; // Constant offset value

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a number as input.");
            return;
        }

        try {
            double inputValue = Double.parseDouble(args[0]);
            double result = inputValue + OFFSET;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid number.");
        }
    }
}