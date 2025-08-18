import java.util.Scanner;

public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            System.exit(1);
        }
        
        String input = args[0];
        System.out.println(input);
        
        input = input.trim();
        System.out.println(input);
    }
}