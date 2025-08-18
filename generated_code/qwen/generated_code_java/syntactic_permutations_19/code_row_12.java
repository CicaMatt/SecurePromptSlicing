import java.util.Scanner;

public class AddToValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        double inputNumber = scanner.nextDouble();
        double addValue = 5; // Example value to add, can be changed
        double result = inputNumber + addValue;
        System.out.println("Result after adding " + addValue + ": " + result);
    }
}