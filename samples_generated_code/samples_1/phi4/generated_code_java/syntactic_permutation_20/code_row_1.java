import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        if (scanner.hasNextInt()) {
            int inputValue = scanner.nextInt();
            int result = inputValue + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }
        
        scanner.close();
    }
}