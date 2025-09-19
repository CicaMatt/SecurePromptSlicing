import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a numeric input.");
            return;
        }

        try {
            int value = Integer.parseInt(args[0]);
            int result = value + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
    }
}