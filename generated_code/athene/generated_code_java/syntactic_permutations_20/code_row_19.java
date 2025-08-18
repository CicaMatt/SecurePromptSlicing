import java.util.Scanner;

public class OffsetValue {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java OffsetValue <number>");
            return;
        }
        
        try {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid number format.");
        }
    }
}