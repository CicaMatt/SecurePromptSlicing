import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length > 0) {
            try {
                int inputValue = Integer.parseInt(args[0]);
                System.out.print("Enter a number to add: ");
                
                while (!scanner.hasNextInt()) {
                    System.out.println("That's not a valid number. Please enter an integer:");
                    scanner.next(); // discard non-integer input
                }
                
                int additionalValue = scanner.nextInt();
                int result = inputValue + additionalValue;
                System.out.println("The result is: " + result);
            } catch (NumberFormatException e) {
                System.out.println("Invalid command line argument. Please provide an integer value.");
            }
        } else {
            System.out.println("No input value provided via command line. Please run the program with a numeric argument.");
        }

        scanner.close();
    }
}