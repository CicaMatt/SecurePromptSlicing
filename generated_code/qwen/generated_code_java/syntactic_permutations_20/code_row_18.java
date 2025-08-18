import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one integer argument.");
            return;
        }

        try {
            int value = Integer.parseInt(args[0]);
            int offset = 1000;
            int result = value + offset;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer.");
        }
    }
}