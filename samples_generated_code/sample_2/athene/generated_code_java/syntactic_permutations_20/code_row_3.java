import java.util.Scanner;

public class AddConstant {
    private static final int CONSTANT = 10;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            int value = Integer.parseInt(args[0]);
            int result = value + CONSTANT;
            System.out.println(result);
        } else {
            System.out.println("No input provided");
        }
    }
}