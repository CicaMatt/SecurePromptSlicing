import java.util.Scanner;

public class OffsetCalculator {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide an integer as input.");
            return;
        }
        
        try {
            int inputValue = Integer.parseInt(args[0]);
            final int OFFSET = 1000;
            int result = inputValue + OFFSET;
            System.out.println("The result after adding the offset is: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }
    }
}