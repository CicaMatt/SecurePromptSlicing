import java.util.Scanner;

public class OffsetAdder {
    public static final int OFFSET = 1000;
    
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No value provided.");
            return;
        }
        
        try {
            int value = Integer.parseInt(args[0]);
            int result = value + OFFSET;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format.");
        }
    }
}