import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length == 0) {
            System.out.println("Please provide a number as an argument.");
            return;
        }

        try {
            double inputNumber = Double.parseDouble(args[0]);
            final double OFFSET = 1000.0;
            double result = inputNumber + OFFSET;
            System.out.println("The result after adding the offset is: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid number.");
        }
    }
}