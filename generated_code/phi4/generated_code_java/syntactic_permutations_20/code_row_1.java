import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter a number:");
        double inputNumber;
        
        try {
            inputNumber = Double.parseDouble(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a numeric value.");
            return;
        }
        
        final double OFFSET = 1000.0;
        double result = inputNumber + OFFSET;

        System.out.println("The result after adding the offset is: " + result);
    }
}