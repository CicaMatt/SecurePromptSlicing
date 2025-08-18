import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a numeric argument.");
            return;
        }

        double constantValue = 10.0; // Example of a constant value to add
        double inputValue;

        try {
            inputValue = Double.parseDouble(args[0]);
            double result = inputValue + constantValue;
            System.out.println("The result is: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid number.");
        }
    }
}