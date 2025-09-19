import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        final int OFFSET = 1000;
        
        if (args.length > 0) {
            try {
                int inputNumber = Integer.parseInt(args[0]);
                int result = inputNumber + OFFSET;
                System.out.println("Result: " + result);
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer as a command line argument.");
            }
        } else {
            System.out.println("No value provided. Please pass an integer as a command-line argument.");
        }

        scanner.close();
    }
}