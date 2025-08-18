import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number to add .5: ");
        double input = scanner.nextDouble();

        double result = input + 0.5;
        
        System.out.println("Result: " + result);
        
        scanner.close();
    }
}