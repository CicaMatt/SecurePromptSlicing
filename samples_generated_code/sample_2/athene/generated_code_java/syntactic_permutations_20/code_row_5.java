import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 5;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            try {
                int value = Integer.parseInt(args[0]);
                int result = value + OFFSET;
                System.out.println("Result: " + result);
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer as an argument.");
            }
        } else {
            System.out.println("No input provided. Please provide an integer as an argument.");
        }
    }
}