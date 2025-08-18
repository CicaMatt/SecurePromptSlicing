import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }
        
        Scanner scanner = new Scanner(args[0]);
        int inputValue = 0;
        try {
            inputValue = scanner.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
            return;
        }
        scanner.close();

        final int CONSTANT_VALUE = 5; // Constant value to add
        int result = inputValue + CONSTANT_VALUE;

        System.out.println("The result is: " + result);
    }
}