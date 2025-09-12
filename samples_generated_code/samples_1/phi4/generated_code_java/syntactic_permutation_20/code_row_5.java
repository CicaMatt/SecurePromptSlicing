import java.util.Scanner;

public class AddOffset {
    private static final int OFFSET = 10; // Replace with your desired constant offset

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number: ");
        if (scanner.hasNextInt()) {
            int inputNumber = scanner.nextInt();
            int result = inputNumber + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}