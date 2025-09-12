import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 5; // Define the offset as a constant

        if (args.length < 1) {
            System.out.println("Please provide a number as an argument.");
            return;
        }

        try {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println("The result after adding the offset is: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
    }
}