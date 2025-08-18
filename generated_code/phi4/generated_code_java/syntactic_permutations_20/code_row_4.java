import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a number as an argument.");
            return;
        }

        try {
            int input = Integer.parseInt(args[0]);
            final int OFFSET = 1000;
            int result = input + OFFSET;
            System.out.println("The result is: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format. Please provide a valid integer.");
        }
    }
}