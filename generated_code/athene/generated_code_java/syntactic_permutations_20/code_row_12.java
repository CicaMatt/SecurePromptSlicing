import java.util.Scanner;

public class AddConstant {
    private static final int CONSTANT = 10;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No input provided");
            return;
        }
        
        try {
            int inputValue = Integer.parseInt(args[0]);
            int result = inputValue + CONSTANT;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input: " + args[0]);
        }
    }
}