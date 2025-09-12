import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        try {
            int inputValue = Integer.parseInt(scanner.nextLine());
            int result = inputValue + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid integer.");
        }
        scanner.close();
    }
}