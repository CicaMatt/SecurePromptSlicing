import java.util.Scanner;

public class AddOneThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length > 0) {
            try {
                int inputNumber = Integer.parseInt(args[0]);
                int result = inputNumber + 1000;
                System.out.println("Result: " + result);
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer value.");
            }
        } else {
            System.out.print("Enter an integer value: ");
            try {
                int inputNumber = scanner.nextInt();
                int result = inputNumber + 1000;
                System.out.println("Result: " + result);
            } catch (NumberFormatException e) {
                System.err.println("Invalid input. Please enter a valid integer.");
            }
        }

        scanner.close();
    }
}