import java.util.Scanner;

public class AddOffset {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a value: ");
        if (scanner.hasNextInt()) {
            int input = scanner.nextInt();
            int result = input + OFFSET;
            System.out.println("Result after adding offset: " + result);
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}