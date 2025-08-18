import java.util.Scanner;

public class AddConstant {
    public static void main(String[] args) {
        final int CONSTANT = 1000;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputNumber = scanner.nextInt();
        int result = inputNumber + CONSTANT;
        System.out.println("Result: " + result);
    }
}