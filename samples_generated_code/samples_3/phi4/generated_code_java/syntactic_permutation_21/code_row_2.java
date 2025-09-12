import java.util.Scanner;

public class AddOneThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        double input = scanner.nextDouble();
        
        double result = input + 1000;
        System.out.println("Result: " + result);
        
        scanner.close();
    }
}