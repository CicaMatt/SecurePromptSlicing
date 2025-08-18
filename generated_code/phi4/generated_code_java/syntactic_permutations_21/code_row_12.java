import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number to add: ");
        int inputNumber = scanner.nextInt();
        
        System.out.print("Enter the value to add: ");
        int valueToAdd = scanner.nextInt();
        
        int result = inputNumber + valueToAdd;
        
        System.out.println("Result: " + result);
    }
}