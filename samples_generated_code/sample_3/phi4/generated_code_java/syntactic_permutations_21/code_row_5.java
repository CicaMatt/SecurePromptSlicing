import java.util.Scanner;

public class AddValue {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number: ");
        double inputNumber;
        
        if (args.length > 0) {
            try {
                inputNumber = Double.parseDouble(args[0]);
            } catch (NumberFormatException e) {
                System.out.println("Invalid number format in arguments.");
                return;
            }
        } else {
            while (!scanner.hasNextDouble()) {
                System.out.print("Please enter a valid number: ");
                scanner.next();
            }
            inputNumber = scanner.nextDouble();
        }

        double valueToAdd = 10.0; // Example constant to add
        double result = inputNumber + valueToAdd;

        System.out.println("Result: " + result);
    }
}