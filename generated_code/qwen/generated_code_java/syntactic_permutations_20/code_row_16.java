import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 5; // Constant offset value
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter a number:");
        String input = scanner.nextLine();

        try {
            int value = Integer.parseInt(input);
            int result = value + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid integer.");
        }

        scanner.close();
    }
}