import java.util.Scanner;

public class AddOneThousand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide a single numeric argument.");
            return;
        }

        try {
            double value = Double.parseDouble(args[0]);
            value += 1000;
            System.out.println(value);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format. Please enter a valid number.");
        }
    }
}