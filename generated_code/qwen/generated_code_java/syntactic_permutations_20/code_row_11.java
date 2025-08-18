import java.util.Scanner;

public class CommandLineInput {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = args[0];
            System.out.println(input + ".");
        } else {
            System.out.println("Please provide a value as a command line argument.");
        }
    }
}