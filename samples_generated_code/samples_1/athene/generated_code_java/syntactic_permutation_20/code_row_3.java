import java.util.Scanner;

public class AddConstant {
    private static final int CONSTANT = 10;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            try {
                int input = Integer.parseInt(args[0]);
                int result = input + CONSTANT;
                System.out.println(result);
            } catch (NumberFormatException e) {
                System.err.println("Invalid number format");
            }
        } else {
            System.err.println("No input provided");
        }
    }
}