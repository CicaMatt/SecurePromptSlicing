import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an integer argument.");
            return;
        }

        int inputNumber;
        try {
            inputNumber = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
            return;
        }

        final int CONSTANT_VALUE = 10; // Change this value as needed
        int result = inputNumber + CONSTANT_VALUE;

        System.out.println("Result: " + result);
    }
}