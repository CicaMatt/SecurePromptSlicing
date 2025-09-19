import java.util.Scanner;

public class CommandLineAdder {

    public static void main(String[] args) {
        final int OFFSET = 10; // Define the constant offset value

        if (args.length < 1) {
            System.out.println("Please provide a numeric input as an argument.");
            return;
        }

        try {
            double inputValue = Double.parseDouble(args[0]);
            double result = inputValue + OFFSET;

            System.out.printf("Input Value: %.2f\n", inputValue);
            System.out.printf("Offset: %d\n", OFFSET);
            System.out.printf("Result: %.2f\n", result);

        } catch (NumberFormatException e) {
            System.out.println("The provided input is not a valid number.");
        }
    }
}