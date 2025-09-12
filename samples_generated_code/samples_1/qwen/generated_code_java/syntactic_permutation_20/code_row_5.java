import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 5;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        if (scanner.hasNextInt()) {
            int value = scanner.nextInt();
            int result = value + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } else {
            System.out.println("Please enter a valid integer.");
        }
        scanner.close();
    }
}