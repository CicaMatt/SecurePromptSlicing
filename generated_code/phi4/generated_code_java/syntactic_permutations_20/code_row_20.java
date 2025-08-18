import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide one numeric argument.");
            return;
        }

        try {
            double input = Double.parseDouble(args[0]);
            final double OFFSET = 1000.0;
            double result = input + OFFSET;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format.");
        }
    }
}