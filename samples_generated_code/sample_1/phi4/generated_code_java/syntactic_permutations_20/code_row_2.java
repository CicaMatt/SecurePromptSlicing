import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        
        if (args.length != 1) {
            System.out.println("Please provide a single integer value as an argument.");
            return;
        }
        
        try {
            int inputValue = Integer.parseInt(args[0]);
            int result = inputValue + OFFSET;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("The provided input is not a valid integer.");
        }
    }
}