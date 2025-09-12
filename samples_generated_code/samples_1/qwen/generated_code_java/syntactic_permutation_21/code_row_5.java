import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputNumber = scanner.nextInt();
        int result = inputNumber + 5; // Assuming we add 5 to the input value
        System.out.println("The result is: " + result);
        System.exit(0);
    }
}