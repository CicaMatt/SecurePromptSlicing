import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 1000;

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