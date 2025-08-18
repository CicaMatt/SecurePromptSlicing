import java.util.Scanner;

public class Adder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int inputNumber = scanner.nextInt();
        
        int result = inputNumber + 1000;
        
        System.out.println("Result after adding 1000: " + result);
    }
}