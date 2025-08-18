import java.util.Scanner;

public class OffsetValue {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            try {
                int value = Integer.parseInt(args[0]);
                int result = value + OFFSET;
                System.out.println(result);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please provide a valid integer.");
            }
        } else {
            System.out.println("No input provided. Please provide an integer as a command-line argument.");
        }
    }
}