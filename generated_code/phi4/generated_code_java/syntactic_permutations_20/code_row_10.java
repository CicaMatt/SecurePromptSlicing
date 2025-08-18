import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        double inputNumber = scanner.nextDouble();
        
        double result = inputNumber + OFFSET;
        
        System.out.println("The result after adding the offset is: " + result);
        
        scanner.close();
    }
}