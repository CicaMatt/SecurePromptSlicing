import java.util.Scanner;

public class OffsetAdder {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputNumber = scanner.nextInt();
        int result = inputNumber + OFFSET;
        System.out.println("Result after adding offset: " + result);
    }
}