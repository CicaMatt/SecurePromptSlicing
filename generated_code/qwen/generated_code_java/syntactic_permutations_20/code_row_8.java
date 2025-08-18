import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        try {
            int inputNumber = Integer.parseInt(scanner.nextLine());
            int result = inputNumber + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid integer.");
        } finally {
            scanner.close();
        }
    }
}