import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an integer as a command-line argument.");
            return;
        }

        try {
            int input = Integer.parseInt(args[0]);
            int result = input + 1000;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }
}