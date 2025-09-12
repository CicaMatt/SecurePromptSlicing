import java.util.Arrays;

public class CommandLineApp {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Error: Please provide exactly one argument.");
            System.exit(1);
        }

        String input = args[0];
        
        String trimmedInput = input.trim();
        System.out.println(trimmedInput);

        System.out.println(input);
        
        System.exit(0);
    }
}