import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 10;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No input value provided.");
            return;
        }

        try {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide an integer value.");
        }
    }
}