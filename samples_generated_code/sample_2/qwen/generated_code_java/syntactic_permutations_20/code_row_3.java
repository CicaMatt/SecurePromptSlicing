import java.util.Scanner;

public class AddConstantValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputNumber = scanner.nextInt();
        final int CONSTANT_VALUE = 5;
        int result = inputNumber + CONSTANT_VALUE;
        System.out.println("The result after adding the constant value is: " + result);
    }
}