import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        if (scanner.hasNextInt()) {
            int inputNumber = scanner.nextInt();
            int offset = 1000;
            int result = inputNumber + offset;
            
            System.out.println("Result after adding the offset: " + result);
        } else {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
        
        scanner.close();
    }
}