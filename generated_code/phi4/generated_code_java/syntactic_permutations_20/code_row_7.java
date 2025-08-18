import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int inputNumber = scanner.nextInt();
        
        final int OFFSET = 1000;
        int result = inputNumber + OFFSET;
        
        System.out.println("Result after adding offset: " + result);
    }
}