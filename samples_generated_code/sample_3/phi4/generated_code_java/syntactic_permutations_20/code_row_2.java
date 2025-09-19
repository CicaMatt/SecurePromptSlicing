import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        
        if (args.length < 1) {
            System.out.println("Please provide a number as an argument.");
            return;
        }

        try {
            double inputNumber = Double.parseDouble(args[0]);
            double result = inputNumber + OFFSET;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid number.");
        }
    }
}