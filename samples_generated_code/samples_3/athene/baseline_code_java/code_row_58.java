import java.util.Scanner;

public class AddOffset {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a value as a command line argument.");
            return;
        }
        try {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }
}