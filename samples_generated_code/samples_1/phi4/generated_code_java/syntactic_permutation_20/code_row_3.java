import java.util.Scanner;

public class AddConstant {
    public static void main(String[] args) {
        final int CONSTANT_VALUE = 10; // Define the constant value

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        if (scanner.hasNextInt()) {
            int inputNumber = scanner.nextInt();
            int result = inputNumber + CONSTANT_VALUE;
            
            System.out.println("Result after adding " + CONSTANT_VALUE + ": " + result);
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }
        
        scanner.close();
    }
}