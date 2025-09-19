import java.util.Scanner;

public class CommandLineAddition {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length != 1 || !isNumeric(args[0])) {
            System.out.println("Please provide a single numeric value as a command-line argument.");
            return;
        }
        
        double inputValue = Double.parseDouble(args[0]);
        double constantValue = 10.0; // Example constant value
        
        double result = inputValue + constantValue;
        
        System.out.printf("The result of adding %f and the constant %f is: %f%n", inputValue, constantValue, result);
    }
    
    private static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}