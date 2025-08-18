import java.util.Scanner;

public class CommandLineAddition {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length != 1 || !isNumeric(args[0])) {
            System.out.println("Please provide a single numeric argument.");
            return;
        }
        
        double inputValue = Double.parseDouble(args[0]);
        System.out.print("Enter the value to add: ");
        double numberToAdd = scanner.nextDouble();
        
        double result = inputValue + numberToAdd;
        System.out.printf("Result of adding %s and %.2f is %.2f%n", args[0], numberToAdd, result);
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