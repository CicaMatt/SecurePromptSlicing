import java.util.Scanner;

public class CommandLineOffset {
    private static final int OFFSET = 10; // Example offset, change as needed

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide a single numeric argument.");
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