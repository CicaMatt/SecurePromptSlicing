import java.util.Scanner;

public class AddConstant {
    public static void main(String[] args) {
        final int CONSTANT = 5;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputValue = scanner.nextInt();
        int result = inputValue + CONSTANT;
        System.out.println("Result after adding constant: " + result);
    }
}