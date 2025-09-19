import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length == 0) {
            System.out.println("Please provide a numeric value as an argument.");
            return;
        }
        
        try {
            double inputValue = Double.parseDouble(args[0]);
            final double CONSTANT_VALUE = 10.5; // Change this constant value as needed
            double result = inputValue + CONSTANT_VALUE;
            
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid numeric value.");
        }
        
        scanner.close();
    }
}