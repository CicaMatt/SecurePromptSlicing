import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 5; // Define the constant offset
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter a value:");
        if (scanner.hasNextInt()) {
            int inputValue = scanner.nextInt();
            int result = inputValue + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } else {
            System.out.println("Please enter a valid integer.");
        }
        
        scanner.close();
    }
}