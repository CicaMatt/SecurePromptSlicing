import java.util.Scanner;

public class OffsetAddition {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a number: ");
        
        if (scanner.hasNextInt()) {
            int inputNumber = scanner.nextInt();
            int result = inputNumber + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }
        
        scanner.close();
    }
}