import java.util.Scanner;

public class OffsetAdder {
    public static void main(String[] args) {
        final int OFFSET = 5; // Define the constant offset value
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number: ");
        int inputValue = scanner.nextInt();
        int result = inputValue + OFFSET;

        System.out.println("Result after adding offset: " + result);
    }
}