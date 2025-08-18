import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            try {
                int value = Integer.parseInt(args[0]);
                int result = value + OFFSET;
                System.out.println(result);
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer.");
            }
        } else {
            System.err.println("No input provided.");
        }
    }
}