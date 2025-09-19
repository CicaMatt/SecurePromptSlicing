import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputNumber = scanner.nextInt();
        int result = inputNumber + 5; // Adding 5 as an example, can be changed
        System.out.println("Result: " + result);
        System.exit(0);
    }
}