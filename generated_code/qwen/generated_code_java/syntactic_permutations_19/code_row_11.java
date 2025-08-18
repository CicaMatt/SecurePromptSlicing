import java.util.Scanner;

public class CommandLineInput {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = args[0];
            System.out.println("The input value is: " + input);
        } else {
            System.out.println("No input value provided.");
        }
    }
}