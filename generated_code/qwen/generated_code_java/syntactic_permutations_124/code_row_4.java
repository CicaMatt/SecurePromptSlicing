import java.util.Arrays;

public class CommandLineArgumentExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Error: Please provide exactly one argument.");
            System.exit(1);
        }
        
        String input = args[0];
        System.out.println("Original Argument: " + input);
        
        input = input.trim();
        System.out.println("Trimmed Argument: " + input);
        
        System.exit(0);
    }
}