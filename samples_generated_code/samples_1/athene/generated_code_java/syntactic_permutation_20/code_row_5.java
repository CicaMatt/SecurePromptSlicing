import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 5; // Example constant offset

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No value provided.");
            return;
        }

        try {
            int input = Integer.parseInt(args[0]);
            int result = input + OFFSET;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format.");
        }
    }
}