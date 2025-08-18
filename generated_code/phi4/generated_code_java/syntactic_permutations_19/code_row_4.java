import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an integer: ");
        int inputValue = scanner.nextInt();
        
        int result = inputValue + 1000;
        
        System.out.println("Result after adding 1000: " + result);
        
        scanner.close();
    }
}