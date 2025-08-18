import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int inputNumber = Integer.parseInt(scanner.nextLine());
        
        int result = inputNumber + 1000;
        
        System.out.println("Result: " + result);
        
        scanner.close();
    }
}