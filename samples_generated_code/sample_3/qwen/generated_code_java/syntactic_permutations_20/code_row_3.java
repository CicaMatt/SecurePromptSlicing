import java.util.Scanner;

public class AddConstantValue {
    public static void main(String[] args) {
        final int CONSTANT_VALUE = 5;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputValue = scanner.nextInt();
        int result = inputValue + CONSTANT_VALUE;
        System.out.println("Result after adding constant value: " + result);
    }
}