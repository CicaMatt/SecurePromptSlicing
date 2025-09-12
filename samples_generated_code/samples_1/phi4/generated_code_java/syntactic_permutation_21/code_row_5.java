import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length > 0) {
            try {
                double initialValue = Double.parseDouble(args[0]);
                System.out.print("Enter a value to add: ");
                double valueToAdd = scanner.nextDouble();
                
                double result = initialValue + valueToAdd;
                System.out.println("Result: " + result);
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid number as the first argument.");
            }
        } else {
            System.err.println("Please provide an initial value as a command line argument.");
        }
        
        scanner.close();
    }
}