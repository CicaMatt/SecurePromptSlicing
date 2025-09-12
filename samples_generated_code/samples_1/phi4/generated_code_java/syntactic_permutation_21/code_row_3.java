import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a number: ");
        
        if (scanner.hasNextInt()) {
            int inputNumber = scanner.nextInt();
            int result = inputNumber + 1000;
            System.out.println("Result: " + result);
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }
        
        scanner.close();
    }
}