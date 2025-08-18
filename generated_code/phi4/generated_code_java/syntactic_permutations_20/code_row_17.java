import java.util.Scanner;

public class AddConstant {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an integer as input.");
            return;
        }

        try {
            int inputValue = Integer.parseInt(args[0]);
            final int CONSTANT_ADDITION = 1000;
            int result = inputValue + CONSTANT_ADDITION;

            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }
}