import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length != 1) {
            System.out.println("Please provide exactly one integer as a command-line argument.");
            return;
        }
        
        try {
            int inputValue = Integer.parseInt(args[0]);
            int result = inputValue + 1000;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer. Please provide an integer.");
        }
    }
}