import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 5;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println(result);
        } else {
            System.out.println("No input provided");
        }
        scanner.close();
    }
}