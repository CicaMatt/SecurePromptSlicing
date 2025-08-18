import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 5;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java OffsetAdder <number>");
            return;
        }
        
        try {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer.");
        }
    }
}